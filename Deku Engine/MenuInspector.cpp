#include "Globals.h"
#include "Application.h"
#include "MenuInspector.h"
#include "Imgui/imgui.h"
#include "GameObject.h"
#include "Component.h"

using namespace std;

// ------------------------------------------------------------
MenuInspector::MenuInspector() : Menu(Menu_Inspector)
{
	UpdatePosSize();
}

// ------------------------------------------------------------
MenuInspector::~MenuInspector()
{}

// ------------------------------------------------------------
void MenuInspector::Render()
{
	GameObject* sel_go = App->editor->selected_go;

	ImGui::Begin("Inspector", &enabled,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoFocusOnAppearing);

	if (sel_go != nullptr)
	{
		// Game Object features ----------------
		bool go_enable = sel_go->IsEnable();

		if (ImGui::Checkbox(sel_go->name.data(), &go_enable))
			sel_go->SetEnable(go_enable);

		// Iterate components ------------------
		vector<Component*>* selected_components = &sel_go->components;

		for (vector<Component*>::const_iterator sel_component = (*selected_components).begin(); sel_component != (*selected_components).end(); ++sel_component)
		{
			(*sel_component)->OnEditor();
		}

		ImGui::Separator();	// -------
		ImGui::Separator();	// -------

		// Add components ----------------------
		if (ImGui::BeginMenu("Add Component"))
		{
			if (ImGui::MenuItem("Transform"))
				sel_go->AddComponent(TRANSFORM);

			if (ImGui::MenuItem("Mesh"))
				sel_go->AddComponent(MESH);

			if (ImGui::MenuItem("Material"))
				sel_go->AddComponent(MATERIAL);

			if (ImGui::MenuItem("Camera"))
				sel_go->AddComponent(CAMERA);

			ImGui::EndMenu();
		}
	}

	ImGui::End();
}

// ------------------------------------------------------------
void MenuInspector::UpdatePosSize()
{
	pos_x = (App->window->GetWidth()) - 302;
	pos_y = 21;
	width = 300;
	height = (App->window->GetHeight()) - 19 - 4;
}