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
		bool comp_enable = enabled;

		if (ImGui::Checkbox("##Material", &comp_enable))
			enabled = comp_enable;

		ImGui::SameLine();
		(enabled) ? (ImGui::Text("(Active)")) : (ImGui::Text("(Desactivated)"));

		ImGui::Separator();	// -------

		ImGui::Image((ImTextureID)name_id, ImVec2(200, 200));
	}
}
