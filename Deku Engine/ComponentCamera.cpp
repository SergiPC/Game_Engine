#include "ComponentCamera.h"
#include "Imgui\imgui.h"

// -----------------------------------------------------------------
ComponentCamera::ComponentCamera(GameObject* owner) : Component(owner, CAMERA)
{}

// -----------------------------------------------------------------
ComponentCamera::~ComponentCamera()
{}

// -----------------------------------------------------------------
bool ComponentCamera::Update()
{
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
void ComponentCamera::OnEditor()
{
	if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Separator();	// -------
	}
}
