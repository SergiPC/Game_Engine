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
	static bool show_test_window = true;
	static bool show_another_window = false;
	static  ImVec4 clear_color = ImColor(114, 144, 154);

	// 1. Show a simple window
	{
		static float f = 0.0f;
		ImGui::Text("Hello, world!");
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::ColorEdit3("clear color", (float*)&clear_color);				
		if (ImGui::Button("Test Window")) show_test_window ^= 1;				
		if (ImGui::Button("Another Window")) show_another_window ^= 1;				
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
	
	// 2. Show another simple window, this time using an explicit Begin/End pair
	if (show_another_window)
	{
		ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
		ImGui::Begin("Another Window", &show_another_window);
		ImGui::Text("Hello");
		ImGui::End();
	}

	// 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
	if (show_test_window)
	{
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool Editor::CleanUp()
{
	LOG("Freeing editor gui");
	ImGui_ImplSdlGL3_Shutdown();

	return true;
}

void Editor::HandleInput(SDL_Event* event)
{
	ImGui_ImplSdlGL3_ProcessEvent(event);
}

void Editor::Draw()
{
	ImGui::Render();
}

bool Editor::IsHovered()
{
	return ImGui::IsAnyItemHovered();
}