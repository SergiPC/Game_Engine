#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "RNG.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");

	c1.size.Set(1.0f, 1.0f, 1.0f);
	c1.SetPos(0,0,0);

	c2.size.Set(1.0f, 1.0f, 1.0f);
	c2.SetPos(1.5f, 0, 0);
	c2.color.Set(0.5f, 0.2f, 0.2f);

	c3.size.Set(1.0f, 1.0f, 1.0f);
	c3.SetPos(3.0f, 0, 0);
	c3.color.Set(0.2f, 0.5f, 0.2f);

	c4.size.Set(1.0f, 1.0f, 1.0f);
	c4.SetPos(4.5f, 0, 0);
	c4.color.Set(0.2f, 0.2f, 0.5f);

	bool ret = true;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update(float dt)
{
	Plane(0, 1, 0, 0).Render();

	c1.Render();
	c2.Render();
	c3.Render();
	c4.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	int a = 0;
}
