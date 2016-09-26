#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "RNG.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");

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

	// Cube by triangles -----------------
	float x = 1.0f;
	float y = 1.0f;
	float z = 1.0f;
	
	float mx = x * 0.5f;
	float my = y * 0.5f;
	float mz = z * 0.5f;
	/*
	float g_vertex_data[] = {
		-mx, -my, -mz,
		-mx, my, -mz,
		mx, -my, -mz,
		mx, -my, -mz,
		-mx, my, -mz,
		mx, my, -mz,
		mx, -my, -mz,
		mx, my, -mz,
		mx, -my, mz,
		mx, -my, mz,
		mx, my, -mz,
		mx, my, mz,
		-mx, -my, mz,
		mx, -my, mz,
		mx, my, mz,
		-mx, -my, mz,
		mx, my, mz,
		-mx, my, mz,
		-mx, -my, -mz,
		-mx, -my, mz,
		-mx, my, mz,
		-mx, -my, -mz,
		-mx, my, mz,
		-mx, my, -mz,
		mx, my, mz,
		mx, my, -mz,
		-mx, my, -mz,
		mx, my, mz,
		-mx, my, -mz,
		-mx, my, mz,
		-mx, -my, mz,
		-mx, -my, -mz,
		mx, -my, -mz,
		-mx, -my, mz,
		mx, -my, -mz,
		mx, -my, mz };
	*/
	glBegin(GL_TRIANGLES);
	// Face -Z -------------------
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-mx, -my, -mz);
	glVertex3f(-mx, my, -mz);
	glVertex3f(mx, -my, -mz);	

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(mx, -my, -mz);
	glVertex3f(-mx, my, -mz);
	glVertex3f(mx, my, -mz);

	// Face X -------------------
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(mx, -my, -mz);
	glVertex3f(mx, my, -mz);
	glVertex3f(mx, -my, mz);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(mx, -my, mz);
	glVertex3f(mx, my, -mz);
	glVertex3f(mx, my, mz);

	// Face Z -------------------
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-mx, -my, mz);
	glVertex3f(mx, -my, mz);
	glVertex3f(mx, my, mz);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-mx, -my, mz);
	glVertex3f(mx, my, mz);
	glVertex3f(-mx, my, mz);

	// Face -X ------------------
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-mx, -my, -mz);
	glVertex3f(-mx, -my, mz);
	glVertex3f(-mx, my, mz);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-mx, -my, -mz);
	glVertex3f(-mx, my, mz);
	glVertex3f(-mx, my, -mz);

	// Face Y -------------------
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(mx, my, mz);
	glVertex3f(mx, my, -mz);
	glVertex3f(-mx, my, -mz);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(mx, my, mz);
	glVertex3f(-mx, my, -mz);
	glVertex3f(-mx, my, mz);

	// Face -Y ------------------
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-mx, -my, mz);
	glVertex3f(-mx, -my, -mz);
	glVertex3f(mx, -my, -mz);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-mx, -my, mz);
	glVertex3f(mx, -my, -mz);
	glVertex3f(mx, -my, mz);

	glEnd();

	glLineWidth(1.0f);

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	int a = 0;
}
