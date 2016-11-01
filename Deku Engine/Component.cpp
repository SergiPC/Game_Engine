#include "Component.h"
#include "GameObject.h"

// -----------------------------------------------------------------
Component::Component(GameObject* owner, Type type) : type(type), owner(owner)
{
	enabled = true;
}

// -----------------------------------------------------------------
Component::~Component()
{}

// -----------------------------------------------------------------
bool Component::Init()
{
	return true;
}

// -----------------------------------------------------------------
bool Component::Update()
{
	return true;
}

// Read only -------------------------------------------------------
const bool Component::IsEnable() const
{
	return enabled;
}

// -----------------------------------------------------------------
void Component::SetEnable(bool enable)
{
	if(enabled != enable)
		enabled = enable;
}

// -----------------------------------------------------------------
void Component::OnEditor()
{}

// Read only -------------------------------------------------------
const Type Component::GetType() const
{
	return type;
}

// Read only -------------------------------------------------------
const GameObject* Component::GetGO() const
{
	return owner;
}