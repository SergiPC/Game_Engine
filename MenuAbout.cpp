#include "MenuAbout.h"
#include "Imgui/imgui.h"

// ------------------------------------------------------------
MenuAbout::MenuAbout() : Menu(Menu_About)
{
	pos_x = 350;
	pos_y = 450;
	width = 600;
	height = 90;
	active = false;
}

// ------------------------------------------------------------
MenuAbout::~MenuAbout()
{}

// ------------------------------------------------------------
void MenuAbout::Render()
{
	ImGui::Begin("Deku Engine", &active,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_HorizontalScrollbar);

	ImGui::Text("3D game engine made for a college's subject.");
	ImGui::Text("By Sergi Perez.");
	ImGui::Separator();
	ImGui::Text("This Engine is licensed under the Public Domain, see LICENSE for more information.");
	ImGui::End();
}
