#ifndef __COMPOENNT_CAMERA_H__
#define __COMPONENT_CAMERA_H__

#include "Component.h"
#include "MathGeoLib/src/MathGeoLib.h"

class ComponentCamera : public Component
{
	ComponentCamera(GameObject* owner);
	~ComponentCamera();

	bool Update();
	void OnEditor();

private:
	Frustum frustum_cam;
};

#endif // !__COMPOENNT_CAMERA_H__
