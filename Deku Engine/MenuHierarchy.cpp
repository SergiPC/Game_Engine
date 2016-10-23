#include "Globals.h"
#include "Application.h"
#include "MenuHierarchy.h"
#include "ModuleGuiEditor.h"
#include "Imgui/imgui.h"
#include "GameObject.h"
#include <vector>

using namespace std;

// ------------------------------------------------------------
MenuHierarchy::MenuHierarchy() : Menu(Menu_Hierarchy)
{
	UpdatePosSize();
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
			(App->editor->selected_go != nullptr) ? (App->go_manager->CreateNewGO(App->editor->selected_go)) : (App->go_manager->CreateNewGO());

		if (ImGui::BeginMenu("Create with..."))
		{
			if (ImGui::MenuItem("Transform"))
			{
				tmp_go = App->go_manager->CreateNewGO();
				tmp_go->AddComponent(TRANSFORM);
			}

			ImGui::EndMenu();
		}

		if (ImGui::MenuItem("Load..."))
			App->go_manager->CreateNewGO();

		ImGui::EndMenu();
	}

	ImGui::Separator();

	// MUST DO 06: draw the hierarchy
	h_root = App->go_manager->GetRoot();
	if (h_root->children.size() > 0)
		RenderChildren(h_root);

	ImGui::End();
}

// ------------------------------------------------------------
void MenuHierarchy::RenderChildren(GameObject* _parent)
{
	vector<GameObject*>::const_iterator it_child;

	for (it_child = _parent->children.begin(); it_child != _parent->children.end(); ++it_child)
	{
		uint flags = 0;

		if ((*it_child) == App->editor->selected_go)
			flags = ImGuiTreeNodeFlags_Selected;		
			
		if ((*it_child)->children.size() != 0)
		{
			if (ImGui::TreeNodeEx((*it_child)->name.data(), flags))
			{
				if (ImGui::IsItemClicked(0))
					App->editor->selected_go = (*it_child);

				RenderChildren((*it_child));

				ImGui::TreePop();
			}
		}

		else
		{
			flags = ImGuiTreeNodeFlags_Leaf;

			if (ImGui::TreeNodeEx((*it_child)->name.data(), flags))
			{
				if (ImGui::IsItemClicked(0))
					App->editor->selected_go = (*it_child);

				ImGui::TreePop();
			}
		}
	}
}

// ------------------------------------------------------------
void MenuHierarchy::UpdatePosSize()
{
	pos_x = (App->window->GetWidth()) - 504;
	pos_y = 21;
	width = 250;
	height = ((App->window->GetHeight()) - 19 - 6) / 2;
}