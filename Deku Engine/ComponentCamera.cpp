#include "Application.h"
#include "GameObject.h"
#include "ComponentCamera.h"
#include "ComponentTransform.h"
#include "Imgui\imgui.h"

// -----------------------------------------------------------------
ComponentCamera::ComponentCamera(GameObject* owner) : Component(owner, CAMERA)
{
	frustum_cam.type = FrustumType::PerspectiveFrustum;

	// Location ------>
	frustum_cam.pos = float3::zero;
	frustum_cam.front = float3::unitZ;
	frustum_cam.up = float3::unitY;

	// Aspect ratio & FOV
	SetRatio(16.f, 9.f, 90.f);
	
	// Planes -------->
	frustum_cam.nearPlaneDistance = 1.0f;
	frustum_cam.farPlaneDistance = 50.0f;

	TransformFrustum();
	
	color_background = { .0f, .0f, .0f, 1.0f };
}

// -----------------------------------------------------------------
ComponentCamera::~ComponentCamera()
{}

// -----------------------------------------------------------------
bool ComponentCamera::Update()
{
	bool ret = true;

	if (enabled)
	{
		// I have to make a flag to know when transform all GO
		TransformFrustum();
		FrustumDebug();
	}

	return ret;
}

// -----------------------------------------------------------------
void ComponentCamera::OnEditor()
{
	if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
	{
		bool comp_enable = enabled;

		if (ImGui::Checkbox("##Camera", &comp_enable))
			enabled = comp_enable;

		ImGui::SameLine();
		(enabled) ? (ImGui::Text("(Active)")) : (ImGui::Text("(Desactivated)"));

		ImGui::Separator();	// -------

		new_horizontal_fov = GetHorizontalFOV();

		if (ImGui::SliderFloat("H. Fov", &new_horizontal_fov, 0.1f, 179.9f, "%.1f", 0.1f))
		{
			// if it's resizable:
			SetHorizontalFOV(new_horizontal_fov);
		}

		ImGui::Text("Vertical Fov::"); ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.25f, 0.88f, 0.81f, 0.70f), "%.1f", frustum_cam.verticalFov * RADTODEG);

		ImGui::Text("Aspect Ratio:"); ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.25f, 0.88f, 0.81f, 0.70f), "%.0f:%.0f (%.1f)", aspect_width, aspect_height, aspect_ratio);
	}
}

// -----------------------------------------------------------------
void ComponentCamera::TransformFrustum()
{
	ComponentTransform* owner_transform = (ComponentTransform*)owner->GetComponent(TRANSFORM);
	float4x4 world_trans = owner_transform->GetWorldTransform();

	frustum_cam.pos = world_trans.TranslatePart();
	frustum_cam.front = world_trans.WorldZ();
	frustum_cam.up = world_trans.WorldY();
}

// -----------------------------------------------------------------
void ComponentCamera::SetRatio(float width, float height, float horizontal_fov)
{
	// Aspect ratio -->
	aspect_width = width;
	aspect_height = height;
	aspect_ratio = aspect_width / aspect_height;

	// FOV ----------->
	SetHorizontalFOV(horizontal_fov);
}

// -----------------------------------------------------------------
void ComponentCamera::SetHorizontalFOV(float horizontal_fov)
{
	// FOV ----------->
	frustum_cam.horizontalFov = DEGTORAD * horizontal_fov;
	frustum_cam.verticalFov = 2.0f * atanf(tanf(frustum_cam.horizontalFov * 0.5f) * (aspect_height / aspect_width));
}

// -----------------------------------------------------------------
const float ComponentCamera::GetHorizontalFOV()
{
	return frustum_cam.horizontalFov * RADTODEG;
}

// -----------------------------------------------------------------
void ComponentCamera::FrustumDebug()
{
	App->renderer3D->RenderFrustum(frustum_cam);
}
