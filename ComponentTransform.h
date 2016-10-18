#ifndef __COMPONENT_TRANSFORM__
#define __COMPONENT_TRANSFORM__

#include "Component.h"

class ComponentTransform : public Component
{
public:
	ComponentTransform(GameObject* _parent);
	~ComponentTransform();

	void		Update();
	void		OnEditor();
	void		SetPos(float new_pos_x, float new_pos_y, float new_pos_z);
	void		SetRotation(float new_rot_x, float new_rot_y, float new_rot_z);
	void		SetScale(float new_scale_x, float new_scale_y, float new_scale_z);

	float3		GetLocalPosition();
	float3		GetLocalRotation();
	float3		GetLocalScale();
	float4x4	GetLocalTransform();
	float4x4	GetWorldTransform();

	float4x4	EulerMatrix(float psi, float theta, float phi);
	float3		MatrixToEuler(float4x4 rot_mat);

private:
	float3		local_position;
	float3		local_rotation;
	float4x4	local_rotation_matrix = local_rotation_matrix.identity;
	float3		local_scale;
	float4x4	local_transform = local_transform.identity;
};

#endif __COMPONENT_TRANSFORM__