#include "Menus.h"
#include "Imgui\imgui.h"

// ------------------------------------------------------------
Menu::Menu(MenuTypes _type) : type(_type)
{}

// ------------------------------------------------------------
Menu::~Menu()
{}

// ------------------------------------------------------------
void Menu::SetEnable(bool enable)
{
	if (enabled != enable)
		enabled = enable;
}

// Read only --------------------------------------------------
const bool Menu::IsEnable() const
{
	return enabled;
}

// ------------------------------------------------------------
void Menu::Render()
{}

// ------------------------------------------------------------
void Menu::UpdatePosSize()
{}

// Read only --------------------------------------------------
const MenuTypes Menu::GetType() const
{
	return type;
}

/*
--------------------------------------------------------------
0 = red
1 = yellow
2 = green
3 = low green
4 = cyan
5 = blue
6 = purple/pink
--------------------------------------------------------------
*/
void Menu::ColorButton(int i_color)
{
	ImGui::PushID(i_color);
	ImGui::PushStyleColor(ImGuiCol_Button, ImColor::HSV(i_color / 7.0f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor::HSV(i_color / 7.0f, 0.7f, 0.7f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImColor::HSV(i_color / 7.0f, 0.8f, 0.8f));

}