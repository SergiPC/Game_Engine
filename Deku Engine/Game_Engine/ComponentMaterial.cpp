#include "ComponentMaterial.h"
#include "Imgui\imgui.h"

// -----------------------------------------------------------------
ComponentMaterial::ComponentMaterial(GameObject* _parent) : Component(_parent, MATERIAL)
{}

// -----------------------------------------------------------------
ComponentMaterial::~ComponentMaterial()
{}

// -----------------------------------------------------------------
void ComponentMaterial::Update()
{}

// -----------------------------------------------------------------
unsigned int ComponentMaterial::GetId()
{
	return name_id;
}

// -----------------------------------------------------------------
void ComponentMaterial::OnEditor()
{
	if (ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Image((ImTextureID)name_id, ImVec2(200, 200));
	}
}