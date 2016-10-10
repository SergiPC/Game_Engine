#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
//#include "MathGeoLib\Math\float3.h"
#include "Glew\include\glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <vector>

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib, "Glew/libx86/glew32.lib")

#define checkImageWidth 64
#define checkImageHeight 64

static GLuint texName;

using namespace std;

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");

	// MUST DO 04: Mesh Component
	// Assimp, first steps -------------------------
	//warrior_fbx = App->load_fbx->LoadFile("Game/Library/warrior.fbx");

	glewInit();

	// MUST DO 03: Texture/Material Component
	// Checkmate texture ---------------------------
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_TEXTURE_2D);

	GLubyte checkImage[checkImageHeight][checkImageWidth][4];
	for (int i = 0; i < checkImageHeight; i++) {
		for (int j = 0; j < checkImageWidth; j++) {
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

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
	glGenBuffers(1, (GLuint*) &(my_vertices));
	glBindBuffer(GL_ARRAY_BUFFER, my_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * 3, vertex, GL_STATIC_DRAW);

	// Create indices buffer
	glGenBuffers(1, (GLuint*) &(my_indices)); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * 6 * 6, indices, GL_STATIC_DRAW);
	*/

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
	PrimPlane(0, 1, 0, 0).Render(); 

	// Paralepipedo 1 by triangles -----------------
	float x = 1.0f;
	float y = 1.0f;
	float z = 1.0f;
	
	float mx = x * 0.5f;
	float my = y * 0.5f;
	float mz = z * 0.5f;
	
	// MUST DO 01: Change Vertex
	glBegin(GL_TRIANGLES);
	// X -------------------
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.f, 0.f); glVertex3f(mx, -my, mz); //A
	glTexCoord2f(0.f, 1.f); glVertex3f(mx, my, -mz); //D
	glTexCoord2f(1.f, 1.f); glVertex3f(mx, my, mz);  //B

	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.f, 1.f); glVertex3f(mx, -my, -mz); //C
	glTexCoord2f(0.f, 1.f); glVertex3f(mx, my, -mz); //D
	glTexCoord2f(1.f, 0.f); glVertex3f(mx, -my, mz); //A

    // Y -------------------
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.f, 0.f); glVertex3f(mx, my, mz); //B
	glTexCoord2f(1.f, 1.f); glVertex3f(mx, my, -mz); //D
	glTexCoord2f(0.f, 1.f); glVertex3f(-mx, my, -mz); //E

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.f, 1.f); glVertex3f(mx, my, mz); //B
	glTexCoord2f(1.f, 0.f); glVertex3f(-mx, my, -mz); //E
	glTexCoord2f(1.f, 1.f); glVertex3f(-mx, my, mz); //F

	// Z -------------------
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1.f, 0.f); glVertex3f(-mx, -my, mz); //G
	glTexCoord2f(1.f, 1.f); glVertex3f(mx, -my, mz); //A
	glTexCoord2f(0.f, 1.f); glVertex3f(mx, my, mz); //B

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.f, 1.f); glVertex3f(-mx, -my, mz); //G
	glTexCoord2f(1.f, 0.f); glVertex3f(mx, my, mz); //B
	glTexCoord2f(1.f, 1.f); glVertex3f(-mx, my, mz); //F

	// -X ------------------
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.f, 0.f); glVertex3f(-mx, -my, -mz);
	glTexCoord2f(0.f, 1.f); glVertex3f(-mx, my, mz);
	glTexCoord2f(1.f, 1.f); glVertex3f(-mx, my, -mz);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.f, 0.f); glVertex3f(-mx, -my, -mz);
	glTexCoord2f(1.f, 1.f); glVertex3f(-mx, -my, mz);
	glTexCoord2f(0.f, 1.f); glVertex3f(-mx, my, mz);

	// -Y ------------------
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(1.f, 0.f); glVertex3f(-mx, -my, mz);
	glTexCoord2f(1.f, 1.f); glVertex3f(-mx, -my, -mz);
	glTexCoord2f(0.f, 1.f); glVertex3f(mx, -my, -mz);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.f, 1.f); glVertex3f(-mx, -my, mz);
	glTexCoord2f(1.f, 0.f); glVertex3f(mx, -my, -mz);
	glTexCoord2f(1.f, 1.f); glVertex3f(mx, -my, mz);

	// -Z -------------------
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.f, 1.f); glVertex3f(mx, -my, -mz);
	glTexCoord2f(1.f, 0.f); glVertex3f(-mx, my, -mz);
	glTexCoord2f(1.f, 1.f); glVertex3f(mx, my, -mz);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(1.f, 1.f); glVertex3f(-mx, -my, -mz);
	glTexCoord2f(0.f, 1.f); glVertex3f(-mx, my, -mz);
	glTexCoord2f(1.f, 0.f); glVertex3f(mx, -my, -mz);


	glEnd();

	// Assimp, first steps -------------------------
	vector<MeshData>::iterator tmp_mesh = warrior_fbx.begin();

	while (tmp_mesh != warrior_fbx.end())
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*tmp_mesh).id_indices);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glDrawElements(GL_TRIANGLES, (*tmp_mesh).num_indices, GL_UNSIGNED_INT, NULL);
		glDisableClientState(GL_VERTEX_ARRAY);

		tmp_mesh++;
	}



	/*
	// Paralepipedo 2 by triangles -----------------
	glEnableClientState(GL_VERTEX_ARRAY); 
	glBindBuffer(GL_ARRAY_BUFFER, my_id); 
	glVertexPointer(3, GL_FLOAT, 0, NULL); 
	// … draw other buffers 
	glDrawArrays(GL_TRIANGLES, 0, 36 * 3); 
	glDisableClientState(GL_VERTEX_ARRAY);


	// Paralepipedo 3 by triangles -----------------
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	// … draw other buffers 
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
	glDisableClientState(GL_VERTEX_ARRAY);
	*/
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	int a = 0;
}
