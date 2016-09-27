#include "Globals.h"
#include "Application.h"
#include "ModuleGuiEditor.h"
#include "ModuleWindow.h"
#include "Menus.h"
#include "MenuAbout.h"

#include "Glew\include\glew.h"
#include "Imgui\imgui_impl_sdl_gl3.h"
#include "Imgui\imgui.h"

ModuleGuiEditor::ModuleGuiEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleGuiEditor::~ModuleGuiEditor()
{
}

// Called before render is available
bool ModuleGuiEditor::Init()
{
	glewInit();
	LOG("Init Editor gui with imgui lib");
	ImGui_ImplSdlGL3_Init(App->window->window);

	// Menus
	menus_list.add(about_menu = new MenuAbout());

	return true;
}
		
update_status ModuleGuiEditor::PreUpdate(float dt)
{
	ImGui_ImplSdlGL3_NewFrame(App->window->window);
	return UPDATE_CONTINUE;
}

// Main loop
update_status ModuleGuiEditor::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;
	static bool show_test_window = true;
	static bool show_menu = true;

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
				if (ImGui::MenuItem("Quit"))
					ret = UPDATE_STOP;

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("View"))
			{
				if (ImGui::MenuItem("Open test window"))
					show_test_window = !show_test_window;

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Help"))
			{
				if (ImGui::MenuItem("About"))
					about_menu->SwitchActive();
				/*
				if (ImGui::MenuItem("Gui Demo"))
					//showcase = !showcase;

				if (ImGui::MenuItem("Documentation"))
					//App->RequestBrowser("https:...");

				if (ImGui::MenuItem("Download latest"))
					//App->RequestBrowser("https:...");

				if (ImGui::MenuItem("Report a bug"))
					//App->RequestBrowser("https:...");
				*/
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}

	// Draw menus
	p2List_item<Menu*>* menu = menus_list.getFirst();

	while (menu != NULL)
	{
		if (menu->data->GetActive() == true)
		{
			ImGui::SetNextWindowPos(ImVec2((float)menu->data->pos_x, (float)menu->data->pos_y), ImGuiSetCond_Always);
			ImGui::SetNextWindowSize(ImVec2((float)menu->data->width, (float)menu->data->height), ImGuiSetCond_Always);
			menu->data->Render();
		}
		menu = menu->next;
	}

	ImGui::Render();

	return ret;
}

// Called before quitting
bool ModuleGuiEditor::CleanUp()
{
	LOG("Freeing Editor gui");
	ImGui_ImplSdlGL3_Shutdown();

	return true;
}