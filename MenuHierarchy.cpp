#include "Globals.h"
#include "Application.h"
#include "MenuHierarchy.h"
#include "Imgui/imgui.h"
#include "GameObject.h"

using namespace std;

// ------------------------------------------------------------
MenuHierarchy::MenuHierarchy() : Menu(Menu_Hierarchy)
{
	pos_x = 2;
	pos_y = 22;
	width = 275;
	height = 475;
}

// ------------------------------------------------------------
MenuHierarchy::~MenuHierarchy()
{}

// ------------------------------------------------------------
void MenuHierarchy::Render()
{
	ImGui::SetNextWindowContentWidth((float)(width * 1.5f));
	ImGui::Begin("Hierarchy", &active,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_HorizontalScrollbar);

	if (ImGui::BeginMenu("Create"))
	{
		if (ImGui::MenuItem("Create Empty"))
			App->go_manager->CreateNewGO();

		if (ImGui::BeginMenu("Create with..."))
		{
			if (ImGui::MenuItem("Transform"))
				App->go_manager->CreateNewGO();

			if (ImGui::MenuItem("Material"))
				App->go_manager->CreateNewGO();

			if (ImGui::BeginMenu("Mesh..."))
			{
				if (ImGui::MenuItem("Cube"))
					App->go_manager->CreateNewGO();

				if (ImGui::MenuItem("Sphere"))
					App->go_manager->CreateNewGO();

				if (ImGui::MenuItem("Cylinder"))
					App->go_manager->CreateNewGO();

				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenu();
	}

	// MUST DO 06: draw the hierarchy
	ImGui::End();
}