#include "Component.h"

// -----------------------------------------------------------------
Component::Component(GameObject* _parent, Type TIPE) : enabled(true), parent(_parent), type(TIPE)
{}

// -----------------------------------------------------------------
void Component::Update()
{}

// -----------------------------------------------------------------
void Component::OnEditor()
{}

// -----------------------------------------------------------------
bool Component::IsEnable()
{
	return enabled;
}

// -----------------------------------------------------------------
void Component::SetEnable(bool enable)
{
	enabled = enable;
}

// -----------------------------------------------------------------
Type Component::GetType()
{
	return type;
}

// -----------------------------------------------------------------
GameObject* Component::GetParent()
{
	return parent;
}

// -----------------------------------------------------------------
bool Component::CleanUp()
{
	return true;
}