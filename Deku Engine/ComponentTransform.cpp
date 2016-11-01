#include "ComponentTransform.h"
#include "GameObject.h"
#include "Imgui\imgui.h"
#include "Math.h"

// -----------------------------------------------------------------
ComponentTransform::ComponentTransform(GameObject* owner) : Component(owner, TRANSFORM),
position(.0f, .0f, .0f), rot_angles(.0f, .0f, .0f), scale(1.0f, 1.0f, 1.0f)
{
	local_transform = local_transform.FromTRS(position, rot_quat, scale);
}

// -----------------------------------------------------------------
ComponentTransform::~ComponentTransform()
{}

// -----------------------------------------------------------------
bool ComponentTransform::Update()
{
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
void ComponentTransform::OnEditor()
{
	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::SameLine();  ImGui::Text("Active");

		ImGui::Separator();	// -------

		if (ImGui::DragFloat3("Position", position.ptr(), 0.1f))
			SetPosition(position);

		if (ImGui::DragFloat3("Rotation", rot_angles.ptr(), 0.1f))
			SetRotation(rot_angles);

		if (ImGui::DragFloat3("Scale", scale.ptr(), 0.1f))
			SetScale(scale);

		ImGui::Separator();	// -------

		if (ImGui::TreeNode("Transform Matrix"))
		{
			float4 row = float4::zero;
			char label[32];

			sprintf(label, "##Row_%u", 0);
			row = world_transform.Row(0);
			ImGui::DragFloat4(label, row.ptr(), .0f, .0f, .0f, "%.1f");

			sprintf(label, "##Row_%u", 2);
			row = world_transform.Row(2);
			ImGui::DragFloat4(label, row.ptr(), .0f, .0f, .0f, "%.1f");

			sprintf(label, "##Row_%u", 1);
			row = world_transform.Row(1);
			ImGui::DragFloat4(label, row.ptr(), .0f, .0f, .0f, "%.1f");

			sprintf(label, "##Row_%u", 3);
			row = world_transform.Row(3);
			ImGui::DragFloat4(label, row.ptr(), .0f, .0f, .0f, "%.1f");

			ImGui::TreePop();
		}
	}
}

// -----------------------------------------------------------------
void ComponentTransform::SetPosition(float3 new_pos)
{
	position = new_pos;

	local_transform = local_transform.FromTRS(position, rot_quat, scale);
	world_transform = GetWorldTransform();

	// Update Bounding Box ----
	owner->UpdateBBox(world_transform, scale);
}

// -----------------------------------------------------------------
void ComponentTransform::SetRotation(float3 new_rot)
{
	rot_angles = new_rot;
	rot_quat = rot_quat.FromEulerXYZ((rot_angles.x * pi) / 180, (rot_angles.y * pi) / 180, (rot_angles.z * pi) / 180);
	
	local_transform = local_transform.FromTRS(position, rot_quat, scale);
	world_transform = GetWorldTransform();

	// Update Bounding Box ----
	owner->UpdateBBox(world_transform, scale);
}

// -----------------------------------------------------------------
void ComponentTransform::SetRotationQuat(Quat new_quat)
{
	rot_angles = new_quat.ToEulerXYZ();
	rot_quat = new_quat;

	local_transform = local_transform.FromTRS(position, rot_quat, scale);
	world_transform = GetWorldTransform();

	// Update Bounding Box ----
	owner->UpdateBBox(world_transform, scale);
}

// -----------------------------------------------------------------
void ComponentTransform::SetScale(float3 new_scale)
{
	scale = new_scale;

	local_transform = local_transform.FromTRS(position, rot_quat, scale);
	world_transform = GetWorldTransform();

	// Update Bounding Box ----
	owner->UpdateBBox(world_transform, scale);
}

// -----------------------------------------------------------------
float3 ComponentTransform::GetPosition() const
{
	return position;
}

// -----------------------------------------------------------------
float3 ComponentTransform::GetRotationAngles() const
{
	return rot_angles;
}

// -----------------------------------------------------------------
float3 ComponentTransform::GetScale() const
{
	return scale;
}

// -----------------------------------------------------------------
float4x4 ComponentTransform::GetWorldTransform() const
{
	math::float4x4 tmp_trans = local_transform;

	if (owner->parent != nullptr)
	{
		ComponentTransform* parentTransform = (ComponentTransform*)owner->parent->GetComponent(TRANSFORM);
		
		if(parentTransform != nullptr)
			tmp_trans =  parentTransform->GetWorldTransform() * tmp_trans;
	}

	return tmp_trans;
}

// -----------------------------------------------------------------
float4x4 ComponentTransform::GetLocalTransform() const
{
	return local_transform;
}

// -----------------------------------------------------------------
float4x4 ComponentTransform::EulerMatrix(float3 euler_angle) const
{
	// x = psi
	// y = theta
	// z = phi

	float cU = cos((euler_angle.x * pi) / 180);	// angle in radians = angle in degrees * pi/180
	float sU = sin((euler_angle.x * pi) / 180);

	float cO = cos((euler_angle.y * pi) / 180);
	float sO = sin((euler_angle.y * pi) / 180);

	float co = cos((euler_angle.z * pi) / 180);
	float so = sin((euler_angle.z * pi) / 180);

	float4x4 R = float4x4(cO*co, cO*so, -sO, 0.0f,
		(co*sU*sO) - (cU*so), (sU*sO*so) + (co*cU), cO*sU, 0.0f,
		(cU*co*sO) + (sU*so), (cU*sO*so) - (co*sU), cO*cU, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f);

	return R;
}

// -----------------------------------------------------------------
float3 ComponentTransform::MatrixToEuler(float4x4 rot_mat)
{
	//float3 rot_euler = rot_mat.ToEulerXYZ();

	// x = psi
	// y = theta
	// z = phi

	float tol = 1E-16;

	if (rot_mat[1][3] < 1.0f)
	{
		if (rot_mat[1][3] > -1.0f)
		{
			rot_euler.x = atan2(-1.0f * rot_mat[2][3], rot_mat[3][3]);
			rot_euler.y = asin(rot_mat[1][3]);
			rot_euler.z = atan2(-1.0f * rot_mat[1][2], rot_mat[1][1]);
		}

		else
		{
			rot_euler.x = -1.0f * atan2(rot_mat[2][1], rot_mat[2][2]);
			rot_euler.y = -pi / 2;
			rot_euler.z = 0.0f;
		}
	}

	else
	{
		rot_euler.x = atan2(rot_mat[2][1], rot_mat[2][2]);
		rot_euler.y = pi / 2;
		rot_euler.z = 0.0f;
	}

	return rot_euler;
}