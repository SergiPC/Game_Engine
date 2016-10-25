#ifndef __COMPONENT_TRANSFORM_H__
#define __COMPONENT_TRANSFORM_H__

#include "Component.h"
#include "MathGeoLib/src/MathGeoLib.h"

class ComponentTransform : public Component
{
public:
	ComponentTransform(GameObject* owner);
	~ComponentTransform();
	
	bool		Update();
	void		OnEditor();
	void		SetPosition(float3 new_pos);
	void		SetRotation(float3 new_rot);
	void		SetRotationQuat(Quat new_quat);
	void		SetScale(float3 new_scale);

	float3		GetPosition() const;
	float3		GetRotationAngles() const;
	float3		GetScale() const;

	float4x4	GetLocalTransform() const;
	float4x4	GetWorldTransform() const;
	float4x4	EulerMatrix(float3 euler_angle) const;
	float3		MatrixToEuler(float4x4 rot_mat);

private:
	float3		position = float3::zero;
	float3		rot_angles = float3::zero;
	float3		rot_euler = float3::zero;
	Quat		rot_quat = Quat::identity;
	float3		scale = float3::zero;
	float4x4	local_transform = float4x4::zero;
	float4x4	world_transform = float4x4::zero;
	//math::OBB	tmp_Obb;
};

#endif __COMPONENT_TRANSFORM_H__