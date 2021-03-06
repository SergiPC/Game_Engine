#ifndef __COMPONENT_CAMERA_H__
#define __COMPONENT_CAMERA_H__

#include "Component.h"
#include "MathGeoLib/src/MathBuildConfig.h"
#include "MathGeoLib/src/MathGeoLib.h"

class ComponentCamera : public Component
{
public:
	ComponentCamera(GameObject* owner);
	~ComponentCamera();

	bool Update();
	void OnEditor();
	void TransformFrustum();

	void SetRatio(float width, float height, float horizontal_fov);
	void CreateRatio();
	void SetHorizontalFOV(float horizontal_fov);
	void SetVerticalFOV(float vertical_fov);

	const float GetHorizontalFOV();
	const float GetVerticalFOV();

	void FrustumDebug();

private:
	Frustum frustum_cam;
	float4 color_background = float4::zero;
	float aspect_ratio = .0f;
	float aspect_width = 0;
	float aspect_height = 0;
	float field_of_view = .0f;
	bool aspect_block = true;
	bool play_cam = false;

	// OnEdit() update variables
	float new_fov = .0f;
	float asp_rat_vec[2] = {.0f, .0f};
};

#endif // !__COMPONENT_CAMERA_H__
