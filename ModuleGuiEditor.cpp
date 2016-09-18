#include "Globals.h"
#include "Application.h"
#include "ModuleGuiEditor.h"
#include "ModuleWindow.h"

#include "Imgui\imgui_impl_sdl_gl3.h"
#include "Imgui\imgui.h"
#include "Imgui\GL\gl3w.h"

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
	gl3wInit();
	LOG("Init Editor gui with imgui lib");
	ImGui_ImplSdlGL3_Init(App->window->window);
	return true;
	rand();
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
					show_test_window = true;

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
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