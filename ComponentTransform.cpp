#include "ComponentTransform.h"
#include "Imgui/imgui.h"

// -----------------------------------------------------------------
ComponentTransform::ComponentTransform(GameObject* _parent) : Component(_parent, TRANSFORM), 
local_position(.0f, .0f, .0f), local_rotation(.0f, .0f, .0f), local_scale(1.0f, 1.0f, 1.0f)
{}

// -----------------------------------------------------------------
ComponentTransform::~ComponentTransform()
{}

// -----------------------------------------------------------------
void ComponentTransform::Update()
{}

// -----------------------------------------------------------------
void ComponentTransform::OnEditor()
{
	float3 new_pos = local_position;
	float3 new_rot = local_rotation;
	float3 new_scale = local_scale;

	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Position", (float*)&new_pos, 0.1f))
			SetPos(new_pos.x, new_pos.y, new_pos.z);

		if (ImGui::DragFloat3("Rotation", (float*)&new_rot, 0.1f))
			SetRotation(new_rot.x, new_rot.y, new_rot.z);

		if (ImGui::DragFloat3("Scale", (float*)&new_scale, 0.1f))
			SetScale(new_scale.x, new_scale.y, new_scale.z);
	}
}

// -----------------------------------------------------------------
void ComponentTransform::SetPos(float new_pos_x, float new_pos_y, float new_pos_z)
{
	local_position.x = new_pos_x;
	local_position.y = new_pos_y;
	local_position.z = new_pos_z;

	SetTransform();
}

// -----------------------------------------------------------------
void ComponentTransform::SetRotation(float new_rot_x, float new_rot_y, float new_rot_z)
{
	local_rotation.x = new_rot_x;
	local_rotation.y = new_rot_y;
	local_rotation.z = new_rot_z;

	local_rotation_matrix = EulerMatrix(local_rotation.x, local_rotation.y, local_rotation.z);
	SetTransform();
}

// -----------------------------------------------------------------
void ComponentTransform::SetScale(float new_scale_x, float new_scale_y, float new_scale_z)
{
	local_scale.x = new_scale_x;
	local_scale.y = new_scale_y;
	local_scale.z = new_scale_z;

	SetTransform();
}

// -----------------------------------------------------------------
void ComponentTransform::SetTransform()
{
	local_transform = local_transform.FromTRS(local_position, local_rotation_matrix, local_scale);
}

// -----------------------------------------------------------------
float3 ComponentTransform::GetLocalPosition()
{
	return local_position;
}

// -----------------------------------------------------------------
float3 ComponentTransform::GetLocalRotation()
{
	return local_rotation;
}

// -----------------------------------------------------------------
float3 ComponentTransform::GetLocalScale()
{
	return local_scale;
}

// -----------------------------------------------------------------
float4x4 ComponentTransform::GetLocalTransform()
{
	return local_transform;
}

// -----------------------------------------------------------------
float4x4 ComponentTransform::EulerMatrix(float psi, float theta, float phi)
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

// -----------------------------------------------------------------
float3 ComponentTransform::MatrixToEuler(float4x4 rot_mat)
{
	float3 euler_angle;
	//float3 euler_angle = rot_mat.ToEulerXYZ();

	// X = psi
	// Y = theta
	// Z = phi

	float tol = 1E-16;

	if (rot_mat[1][3] < 1.0f)
	{
		if (rot_mat[1][3] > -1.0f)
		{
			euler_angle.x = atan2(-1.0f * rot_mat[2][3], rot_mat[3][3]);
			euler_angle.y = asin(rot_mat[1][3]);
			euler_angle.z = atan2(-1.0f * rot_mat[1][2], rot_mat[1][1]);
		}

		else
		{
			euler_angle.x = -1.0f * atan2(rot_mat[2][1], rot_mat[2][2]);
			euler_angle.y = -pi / 2;
			euler_angle.z = 0.0f;
		}
	}

	else
	{
		euler_angle.x = atan2(rot_mat[2][1], rot_mat[2][2]);
		euler_angle.y = pi / 2;
		euler_angle.z = 0.0f;
	}

	return euler_angle;
}