#include "Globals.h"
#include "Application.h"
#include "Editor.h"
#include "ModuleWindow.h"

#include "Imgui\imgui_impl_sdl_gl3.h"
#include "Imgui\imgui.h"
#include "Imgui\GL\gl3w.h"

Editor::Editor(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
Editor::~Editor()
{
}

// Called before render is available
bool Editor::Init()
{
	gl3wInit();
	LOG("Init editor gui with imgui lib");
	ImGui_ImplSdlGL3_Init(App->window->window);
	return true;
}
		
update_status Editor::PreUpdate(float dt)
{
	ImGui_ImplSdlGL3_NewFrame(App->window->window);
	return UPDATE_CONTINUE;
}

// Main loop
update_status Editor::Update(float dt)
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
bool Editor::CleanUp()
{
	LOG("Freeing editor gui");
	ImGui_ImplSdlGL3_Shutdown();

	return true;
}