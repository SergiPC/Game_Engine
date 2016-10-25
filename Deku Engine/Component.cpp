#include "Component.h"

// -----------------------------------------------------------------
Component::Component(GameObject* owner, Type type)
{
	this->type = type;
	this->owner = owner;
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
void Component::OnEditor()
{}

// Read only -------------------------------------------------------
Type Component::GetType() const
{
	return type;
}