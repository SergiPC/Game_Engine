#include "Application.h"
#include "ComponentCamera.h"
#include "Imgui\imgui.h"

// -----------------------------------------------------------------
ComponentCamera::ComponentCamera(GameObject* owner) : Component(owner, CAMERA)
{
	frustum_cam.type = FrustumType::PerspectiveFrustum;

	// Location ------>
	frustum_cam.pos = float3::zero;
	frustum_cam.front = float3::unitZ;
	frustum_cam.up = float3::unitY;

	// Aspect ratio -->
	width = 16;
	height = 9;
	aspect_ratio = width / height;

	// Planes -------->
	frustum_cam.nearPlaneDistance = 1.0f;
	frustum_cam.farPlaneDistance = 100.0f;
	frustum_cam.horizontalFov = DEGTORAD * 100.0f;
	frustum_cam.verticalFov = 2.0f * atanf(tanf(frustum_cam.horizontalFov / 2.0f) * (height / width));
	
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

		ImGui::Text("Horizontal Fov::"); ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.25f, 0.88f, 0.81f, 0.70f), "%.1f", frustum_cam.horizontalFov * RADTODEG);

		ImGui::Text("Aspect Ratio:"); ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.25f, 0.88f, 0.81f, 0.70f), "%d:%d", width, height);
	}
}

// -----------------------------------------------------------------
void ComponentCamera::FrustumDebug()
{
	App->renderer3D->RenderFrustum(frustum_cam);
}
