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