#include "Globals.h"
#include "Application.h"
#include "ModuleGuiEditor.h"
#include "Menus.h"
#include "MenuConfig.h"
#include "MenuInspector.h"
#include "MenuHierarchy.h"
#include "MenuAbout.h"
#include "GameObject.h"

#include "Imgui\imgui.h"
#include "Imgui\imgui_impl_sdl_gl3.h"
#include "Glew\include\glew.h"
#pragma comment (lib, "Glew/libx86/glew32.lib")

using namespace std;

// ------------------------------------------------------------
ModuleGuiEditor::ModuleGuiEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

// Destructor -------------------------------------------------
ModuleGuiEditor::~ModuleGuiEditor()
{}

// Called before render is available --------------------------
bool ModuleGuiEditor::Init()
{
	glewInit();
	LOG("Init Editor gui with imgui lib");
	ImGui_ImplSdlGL3_Init(App->window->window);

	// Add Menus
	menus_list.push_back(about_menu = new MenuAbout());
	menus_list.push_back(hierarchy_menu = new MenuHierarchy());
	menus_list.push_back(diagnostic_menu = new MenuConfig());
	menus_list.push_back(inspector_menu = new MenuInspector());

	return true;
}

// ------------------------------------------------------------
update_status ModuleGuiEditor::PreUpdate(float dt)
{
	ImGui_ImplSdlGL3_NewFrame(App->window->window);
	return UPDATE_CONTINUE;
}

// Main loop --------------------------------------------------
update_status ModuleGuiEditor::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;
	static bool show_test_window = false;

	if (show_test_window)
	{
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);
	}

	// Create top menu
	if (show_menu == true)
	{
		if (ImGui::BeginMainMenuBar())
		{
			bool selected = false;

			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New Scene", "    Ctrl+N"))
				{
					//ret = UPDATE_STOP;
				}

				if (ImGui::BeginMenu("Open Scene", "    Ctrl+O"))
				{
					if (ImGui::MenuItem("Village"))
						App->load_mesh->LoadFile("Library/Mesh/Street environment_V01.FBX");

					//if (ImGui::MenuItem("Warrior"))
					//App->load_mesh->LoadFile("Library/Mesh/warrior.FBX");

					ImGui::EndMenu();
				}

				if (ImGui::MenuItem("Save Scene", "    Ctrl+S"))
				{
					//ret = UPDATE_STOP;
				}

				ImGui::Separator();

				if (ImGui::MenuItem("Quit", "    Esc"))
					ret = UPDATE_STOP;

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Window"))
			{
				if (ImGui::MenuItem("Hierarchy", "    Ctrl+1"))
				{
					selected = hierarchy_menu->IsEnable();
					hierarchy_menu->SetEnable(!selected);
				}

				if (ImGui::MenuItem("Inspector", "    Ctrl+2"))
				{
					selected = inspector_menu->IsEnable();
					inspector_menu->SetEnable(!selected);
				}

				if (ImGui::MenuItem("Configuration", "    Ctrl+3"))
				{
					selected = diagnostic_menu->IsEnable();
					diagnostic_menu->SetEnable(!selected);
				}

				if (ImGui::MenuItem("Test", "    Ctrl+4"))
					show_test_window = !show_test_window;

				ImGui::Separator();

				if (ImGui::MenuItem("Console", "    Ctrl+Shift+C"))
					show_test_window = !show_test_window;

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Help"))
			{
				if (ImGui::MenuItem("About"))
				{
					selected = about_menu->IsEnable();
					about_menu->SetEnable(!selected);
				}

				ImGui::Separator();

				if (ImGui::MenuItem("Documentation", "    ->"))
				{
					//ShellExecute(NULL, "open", "https://github.com/SergiPC/Game_Engine/wiki", NULL, NULL, SW_SHOWDEFAULT);
					App->ExecuteBrowser("https://github.com/SergiPC/Game_Engine/wiki");
				}

				if (ImGui::MenuItem("Download latest", "    ->"))
					App->ExecuteBrowser("https://github.com/SergiPC/Game_Engine/releases");

				if (ImGui::MenuItem("Report a bug", "    ->"))
					App->ExecuteBrowser("https://github.com/SergiPC/Game_Engine/issues");

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}

	// Draw menus
	vector<Menu*>::iterator tmp;	// declare an iterator for a vector

	for (tmp = menus_list.begin(); tmp != menus_list.end(); ++tmp)
	{
		Menu* current_menu = *tmp;

		if (current_menu->IsEnable() == true)
		{
			ImGui::SetNextWindowPos(ImVec2((float)current_menu->pos_x, (float)current_menu->pos_y), ImGuiSetCond_Always);
			ImGui::SetNextWindowSize(ImVec2((float)current_menu->width, (float)current_menu->height), ImGuiSetCond_Always);
			current_menu->Render();
		}
	}

	ImGui::Render();

	return ret;
}

// ------------------------------------------------------------
void ModuleGuiEditor::UpdatePosSize()
{
	vector<Menu*>::iterator tmp;	// declare an iterator for a vector

	for (tmp = menus_list.begin(); tmp != menus_list.end(); ++tmp)
	{
		Menu* current_menu = *tmp;

		current_menu->UpdatePosSize();
	}
}


// ------------------------------------------------------------
void ModuleGuiEditor::CalcPar(float current_fps, float current_ms)
{
	if (diagnostic_menu->IsEnable())
		diagnostic_menu->CalculateParameters(current_fps, current_ms);
}

// Called before quitting -------------------------------------
bool ModuleGuiEditor::CleanUp()
{
	LOG("Freeing Editor gui");
	ImGui_ImplSdlGL3_Shutdown();

	return true;
}