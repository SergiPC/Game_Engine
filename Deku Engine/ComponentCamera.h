#ifndef __COMPONENT_CAMERA_H__
#define __COMPONENT_CAMERA_H__

#include "Component.h"
#include "MathGeoLib/src/MathGeoLib.h"

class ComponentCamera : public Component
{
public:
	ComponentCamera(GameObject* owner);
	~ComponentCamera();

	bool Update();
	void OnEditor();

	void FrustumDebug();

private:
	Frustum frustum_cam;
	float4 color_background = float4::zero;
	float aspect_ratio = .0f;
	int width = 0;
	int height = 0;
	float field_of_view = .0f;
	bool resizable = false;
};

#endif // !__COMPONENT_CAMERA_H__
