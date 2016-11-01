#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "p2List.h"
#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleFileSystem.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModulePhysics3D.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleGuiEditor.h"
#include "ModuleLoadMesh.h"
#include "ModuleGOManager.h"

class Application
{
public:
	ModuleFileSystem* file_sys;
	ModuleWindow* window;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleSceneIntro* scene_intro;
	ModulePhysics3D* physics3D;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleGuiEditor* editor;
	ModuleLoadMesh* load_mesh;
	ModuleGOManager* go_manager;

private:
	Timer	ms_timer;
	Timer	fps_timer;
	Uint32	frames;
	float	dt;
	int		fps_counter;
	int		last_frame_ms;
	int		last_fps;
	int		capped_ms;
	p2List<Module*> list_modules;

	std::string title;
	std::string organization;

public:
	Application();
	~Application();

	bool			Init();
	update_status	Update();
	bool			CleanUp();

	// Exposing some properties for reading
	const char*		GetTitle() const;
	const char*		GetOrganizationName() const;
	void			ExecuteBrowser(const char* path);

private:
	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};

extern Application* App;

#endif __APPLICATION_H__