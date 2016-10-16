#include "Globals.h"
#include "Application.h"
#include "MenuInspector.h"
#include "Imgui/imgui.h"
#include "GameObject.h"


using namespace std;

// ------------------------------------------------------------
MenuInspector::MenuInspector() : Menu(Menu_Inspector)
{
	pos_x = (App->window->GetWidth()) - 252;
	pos_y = 21;
	width = 250;
	height = ((App->window->GetHeight()) - 19 - 6) / 2;	// Provisional :(
}

// ------------------------------------------------------------
MenuInspector::~MenuInspector()
{}

// ------------------------------------------------------------
void MenuInspector::Render()
{
	GameObject* sel_go = App->editor->selected_go;

	ImGui::SetNextWindowContentWidth((float)(width * 1.5f));
	ImGui::Begin("Inspector", &active,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoFocusOnAppearing);

	if (sel_go != nullptr)
	{
		bool go_enable = sel_go->IsEnable();

		if (ImGui::Checkbox("", &go_enable))
			sel_go->SetEnable(go_enable);
		
		// Name --------------------------------
		ImGui::SameLine();  ImGui::Text(sel_go->name.data());

		// Iterate components ------------------
		vector<Component*>* selected_components = &sel_go->components;

		for (vector<Component*>::const_iterator sel_component = (*selected_components).begin(); sel_component != (*selected_components).end(); ++sel_component)
		{
			(*sel_component)->OnEditor();
		}

		ImGui::Separator();

		// Add components ----------------------
		if (ImGui::BeginMenu("Add Component"))
		{
			if (ImGui::MenuItem("Transform"))
				sel_go->AddComponent(TRANSFORM);

			if (ImGui::MenuItem("Mesh"))
				sel_go->AddComponent(MESH);

			if (ImGui::MenuItem("Material"))
				sel_go->AddComponent(MATERIAL);

			ImGui::EndMenu();
		}
	}

	ImGui::End();
}