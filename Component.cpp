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
Transform::Transform() : Component(), position(1.0f, 1.0f, 1.0f), rotation(.0f, .0f, .0f), scale(1.0f, 1.0f, 1.0f), tranform(tranform.identity)
{
	type = Type::TRANSFORM;
}

void Transform::Update()
{}

void Transform::SetPos(float npos_x, float npos_y, float npos_z)
{
	position.x = npos_x;
	position.y = npos_y;
	position.z = npos_z;
}

void Transform::SetRotation(float nrot_x, float nrot_y, float nrot_z)
{
	rotation.x = nrot_x;
	rotation.y = nrot_y;
	rotation.z = nrot_z;
	// Do rotation math: euler angles -> quaternion -> tranform
}

void Transform::SetScale(float nscale_x, float nscale_y, float nscale_z)
{
	scale.x = nscale_x;
	scale.y = nscale_y;
	scale.z = nscale_z;
}

float4x4 Transform::EulerMatrix(float psi, float theta, float phi)
{
	float cU = cos((psi * pi) / 180);	// angle in radians = angle in degrees * pi/180
	float sU = sin((psi * pi) / 180);

	float cO = cos((theta * pi) / 180);
	float sO = sin((theta * pi) / 180);

	float co = cos((phi * pi) / 180);
	float so = sin((phi * pi) / 180);

	float4x4 R = float4x4(cO*co, cO*so, -sO, 0.0f,
	(co*sU*sO) - (cU*so), (sU*sO*so) + (co*cU), cO*sU, 0.0f,
	(cU*co*sO) + (sU*so), (cU*sO*so) - (co*sU), cO*cU, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f);

	return R;
}

float3 Transform::MatrixToEuler(float4x4 rot_mat)
{
	float3 e_ang = rot_mat.ToEulerXYZ();

	// X = psi
	// Y = theta
	// Z = phi

	float tol = 1E-16;

	if (rot_mat[1][3] < 1.0f)
	{
		if (rot_mat[1][3] > -1.0f)
		{
			e_ang.x = atan2(-1.0f * rot_mat[2][3], rot_mat[3][3]);
			e_ang.y = asin(rot_mat[1][3]);
			e_ang.z = atan2(-1.0f * rot_mat[1][2], rot_mat[1][1]);
		}

		else
		{
			e_ang.x = -1.0f * atan2(rot_mat[2][1], rot_mat[2][2]);
			e_ang.y = -pi / 2;
			e_ang.z = 0.0f;
		}
	}

	else
	{
		e_ang.x = atan2(rot_mat[2][1], rot_mat[2][2]);
		e_ang.y = pi / 2;
		e_ang.z = 0.0f;
	}

	return e_ang;
}