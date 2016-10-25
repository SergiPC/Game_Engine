#include "ComponentMaterial.h"
#include "Imgui\imgui.h"

// -----------------------------------------------------------------
ComponentMaterial::ComponentMaterial(GameObject* owner) : Component(owner, MATERIAL)
{}

// -----------------------------------------------------------------
ComponentMaterial::~ComponentMaterial()
{}

// -----------------------------------------------------------------
bool ComponentMaterial::Update()
{
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
void ComponentMaterial::OnEditor()
{
	if (ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen))
	{
		bool comp_enable = this->enabled;

		if (ImGui::Checkbox("", &comp_enable))
			this->enabled = comp_enable;

		ImGui::SameLine();  ImGui::Text("Active");

		ImGui::Separator();	// -------

		ImGui::Image((ImTextureID)name_id, ImVec2(200, 200));
	}
}
