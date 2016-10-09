#ifndef __COMPONENT__
#define __COMPONENT__

//#include "glmath.h"
#include "MathGeoLib/MathBuildConfig.h"
#include "MathGeoLib/MathGeoLib.h"

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
	void		Update();
	void		SetPos(float npos_x, float npos_y, float npos_z);
	void		SetRotation(float nrot_x, float nrot_y, float nrot_z);
	void		SetScale(float nscale_x, float nscale_y, float nscale_z);

	float4x4	EulerMatrix(float psi, float theta, float phi);
	float3		MatrixToEuler(float4x4 rot_mat);

private:
	float3		position;
	float3		rotation;
	float3		scale;
	float4x4	tranform;
	float4		quat;
};

#endif __COMPONENT__