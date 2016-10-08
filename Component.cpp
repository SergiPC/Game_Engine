#include "Component.h"

// -----------------------------------------------------------------
Component::Component() : enabled(true)
{}

// -----------------------------------------------------------------
void Component::Update(float dt)
{

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
Type Component::GetType()
{
	return type;
}

// -----------------------------------------------------------------
bool Component::CleanUp()
{
	return true;
}

// TRANFORM ========================================
// -----------------------------------------------------------------
Transform::Transform() : Component(), position(1.0f, 1.0f, 1.0f), rotation(.0f, .0f, .0f), scale(1.0f, 1.0f, 1.0f), tranform(IdentityMatrix)
{
	type = Type::TRANSFORM;
}

void Transform::Update()
{}

void Transform::SetPos(vec3 new_pos)
{
	position = new_pos;
}

void Transform::SetRotation(vec3 new_rotation)
{
	rotation = new_rotation;
	// Do rotation math: euler angles -> quaternion -> tranform
}

void Transform::SetScale(vec3 new_scale)
{
	scale = new_scale;
}