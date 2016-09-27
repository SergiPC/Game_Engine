#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "RNG.h"
#include "OpenGL.h"

#pragma comment (lib, "Glew/libx86/glew32.lib") /* link Microsoft OpenGL lib   */

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	/*
	my_id = 0;

	// Paralepipedo 2 by triangles -----------------
	float x2 = 5.0f;
	float y2 = 5.0f;
	float z2 = 5.0f;

	float mx2 = x2 * 0.5f;
	float my2 = y2 * 0.5f;
	float mz2 = z2 * 0.5f;

	float g_vertex_data[] = {
		-mx2, -my2, -mz2,
		-mx2, my2, -mz2,
		mx2, -my2, -mz2,
		mx2, -my2, -mz2,
		-mx2, my2, -mz2,
		mx2, my2, -mz2,
		mx2, -my2, -mz2,
		mx2, my2, -mz2,
		mx2, -my2, mz2,
		mx2, -my2, mz2,
		mx2, my2, -mz2,
		mx2, my2, mz2,
		-mx2, -my2, mz2,
		mx2, -my2, mz2,
		mx2, my2, mz2,
		-mx2, -my2, mz2,
		mx2, my2, mz2,
		-mx2, my2, mz2,
		-mx2, -my2, -mz2,
		-mx2, -my2, mz2,
		-mx2, my2, mz2,
		-mx2, -my2, -mz2,
		-mx2, my2, mz2,
		-mx2, my2, -mz2,
		mx2, my2, mz2,
		mx2, my2, -mz2,
		-mx2, my2, -mz2,
		mx2, my2, mz2,
		-mx2, my2, -mz2,
		-mx2, my2, mz2,
		-mx2, -my2, mz2,
		-mx2, -my2, -mz2,
		mx2, -my2, -mz2,
		-mx2, -my2, mz2,
		mx2, -my2, -mz2,
		mx2, -my2, mz2 };

	glGenBuffers(1, (GLuint*) &(my_id));
	glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36 * 3, g_vertex_data, GL_STATIC_DRAW);
	*/
	// Paralepipedo 3 by triangles -----------------
	float x3 = 7.0f;
	float y3 = 7.0f;
	float z3 = 7.0f;

	float mx3 = x3 * 0.5f;
	float my3 = y3 * 0.5f;
	float mz3 = z3 * 0.5f;

	float vertex[] = {
		mx3, -my3, -mz3,
		-mx3, -my3, -mz3,
		mx3, my3, -mz3,
		-mx3, my3, -mz3,
		mx3, -my3, mz3,
		-mx3, -my3, mz3,
		mx3, my3, mz3,
		-mx3, my3, mz3 };

	uint indices[] = { 
		0,1,2, 1,3,2,
		1,5,3, 5,7,3,
		5,4,7, 4,6,7,
		4,0,6, 0,2,6,
		2,3,6, 3,7,6,
		4,5,0, 5,1,0 };

	// Create vertice buffer
	my_vertices = 0;
	glGenBuffers(1, (GLuint*) &(my_vertices));
	glBindBuffer(GL_ARRAY_BUFFER, my_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * 3, vertex, GL_STATIC_DRAW);

	// Create indices buffer
	my_indices = 0;
	glGenBuffers(1, (GLuint*) &(my_indices)); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * 6 * 6, indices, GL_STATIC_DRAW);

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

	// Paralepipedo 1 by triangles -----------------
	float x = 1.0f;
	float y = 1.0f;
	float z = 1.0f;
	
	float mx = x * 0.5f;
	float my = y * 0.5f;
	float mz = z * 0.5f;
	
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
	
	/*
	// Paralepipedo 2 by triangles -----------------
	glEnableClientState(GL_VERTEX_ARRAY); 
	glBindBuffer(GL_ARRAY_BUFFER, my_id); 
	glVertexPointer(3, GL_FLOAT, 0, NULL); 
	// … draw other buffers 
	glDrawArrays(GL_TRIANGLES, 0, 36 * 3); 
	glDisableClientState(GL_VERTEX_ARRAY);
	*/

	// Paralepipedo 3 by triangles -----------------
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	// … draw other buffers 
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
	glDisableClientState(GL_VERTEX_ARRAY);

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	int a = 0;
}
