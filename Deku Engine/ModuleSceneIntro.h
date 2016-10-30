#ifndef __MODULE_SCENE_INTRO_H__
#define __MODULE_SCENE_INTRO_H__

#include "Module.h"

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool			Start();
	update_status	Update(float dt);
	bool			CleanUp();

	void			OnCollision(PhysBody3D* body1, PhysBody3D* body2);
};

#endif __MODULE_SCENE_INTRO_H__