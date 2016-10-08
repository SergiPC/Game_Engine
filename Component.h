#ifndef __COMPONENT__
#define __COMPONENT__

#include "glmath.h"

enum Type
{
	TRANSFORM,
	AUDIO,
	CAMERA,
	MATERIAL,
	MESH
};

class Component
{
public:
	Component();

	virtual void	Update(float dt);
	bool			IsEnable();
	void			SetEnable(bool enable);
	Type			GetType();
	bool			CleanUp();

private:
	bool	enabled;

protected:
	Type	type;
};

// ============================================
class Transform : public Component
{
public:
	Transform();
	void	Update();
	void	SetPos(vec3 new_pos);
	void	SetRotation(vec3 new_rotation);
	void	SetScale(vec3 new_scale);

private:
	vec3		position;
	vec3		rotation;
	vec3		scale;
	mat4x4		tranform;
	vec4		quat;
};

#endif __COMPONENT__