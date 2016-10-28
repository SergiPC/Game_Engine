#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleSceneIntro::~ModuleSceneIntro()
{}

bool ModuleSceneIntro::Start()
{
	bool ret = true;

	// town ----------------------------------------
	//App->load_mesh->LoadFile("Library/Mesh/Street environment_V01.FBX");
	//App->load_mesh->LoadFile("Library/Mesh/warrior.FBX");

	// Checkmate texture ---------------------------
	/*
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
	*/

	return ret;
}

bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	//glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

update_status ModuleSceneIntro::Update(float dt)
{
	Plane(0, 1, 0, 0).Render();

	// parallelepiped 1 by triangles ----------------
	/*
	float x = 1.0f;
	float y = 1.0f;
	float z = 1.0f;

	float mx = x * 0.5f;
	float my = y * 0.5f;
	float mz = z * 0.5f;

	glBegin(GL_TRIANGLES);
	// X -------------------
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.f, 0.f); glVertex3f(mx, -my, mz);
	glTexCoord2f(0.f, 1.f); glVertex3f(mx, my, -mz);
	glTexCoord2f(1.f, 1.f); glVertex3f(mx, my, mz);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.f, 1.f); glVertex3f(mx, -my, -mz);
	glTexCoord2f(0.f, 1.f); glVertex3f(mx, my, -mz);
	glTexCoord2f(1.f, 0.f); glVertex3f(mx, -my, mz);

	// Y -------------------
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.f, 0.f); glVertex3f(mx, my, mz);
	glTexCoord2f(1.f, 1.f); glVertex3f(mx, my, -mz);
	glTexCoord2f(0.f, 1.f); glVertex3f(-mx, my, -mz);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.f, 1.f); glVertex3f(mx, my, mz);
	glTexCoord2f(1.f, 0.f); glVertex3f(-mx, my, -mz);
	glTexCoord2f(1.f, 1.f); glVertex3f(-mx, my, mz);

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

	// Z -------------------
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1.f, 0.f); glVertex3f(-mx, -my, mz);
	glTexCoord2f(1.f, 1.f); glVertex3f(mx, -my, mz);
	glTexCoord2f(0.f, 1.f); glVertex3f(mx, my, mz);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.f, 1.f); glVertex3f(-mx, -my, mz);
	glTexCoord2f(1.f, 0.f); glVertex3f(mx, my, mz);
	glTexCoord2f(1.f, 1.f); glVertex3f(-mx, my, mz);

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
	*/

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}
