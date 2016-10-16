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
//void ComponentMaterial::OnEditor()
//{}