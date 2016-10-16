#ifndef __MODULE_SCENE_INTRO__
#define __MODULE_SCENE_INTRO__

#include "Module.h"
#include "ModuleLoadMesh.h"

#define BOUNCER_TIME 200

struct MeshData;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:

	uint my_id = 0;
	uint my_indices = 0;
	uint my_vertices = 0;
};

#endif __MODULE_SCENE_INTRO__
