#include "Application.h"

// ------------------------------------------------------------
Application::Application()
{
	frames = 0;
	last_frame_ms = -1;
	last_fps = -1;
	capped_ms = 1000 / 60;
	fps_counter = 0;

	file_sys = new ModuleFileSystem(this);
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this, true);
	scene_intro = new ModuleSceneIntro(this);
	physics3D = new ModulePhysics3D(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	editor = new ModuleGuiEditor(this);
	load_mesh = new ModuleLoadMesh(this);
	go_manager = new ModuleGOManager(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order
	
	// Main Modules
	AddModule(file_sys);
	AddModule(window);
	AddModule(physics3D);
	AddModule(renderer3D);
	AddModule(camera);
	AddModule(input);
	AddModule(audio);
	AddModule(load_mesh);
	AddModule(go_manager);

	// Scenes
	AddModule(scene_intro);
	AddModule(editor);
	
	// Characters
	
}

// ------------------------------------------------------------
Application::~Application()
{
	p2List_item<Module*>* item = list_modules.getLast();

	while(item != NULL)
	{
		delete item->data;
		item = item->prev;
	}
}

// ------------------------------------------------------------
bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	p2List_item<Module*>* item = list_modules.getFirst();

	while(item != NULL && ret == true)
	{
		ret = item->data->Init();
		item = item->next;
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	item = list_modules.getFirst();

	while(item != NULL && ret == true)
	{
		if(item->data->IsEnabled())
			ret = item->data->Start();
		item = item->next;
	}
	
	return ret;
}


// ------------------------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();
}

// ------------------------------------------------------------
void Application::FinishUpdate()
{
	// Recap on framecount and fps
	++frames;
	++fps_counter;

	if(fps_timer.Read() >= 1000)
	{
		last_fps = fps_counter;
		fps_counter = 0;
		fps_timer.Start();
	}

	last_frame_ms = ms_timer.Read();

	// cap fps
	if(last_frame_ms < capped_ms)
	{
		SDL_Delay(capped_ms - last_frame_ms);
	}

	//char t[50];
	//sprintf_s(t, "FPS: %d", (int)last_fps);
	//window->SetTitle(t);
	editor->CalcPar((float)last_fps, (float)last_frame_ms);
}

// Call PreUpdate, Update and PostUpdate on all modules -------
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	p2List_item<Module*>* item = list_modules.getFirst();
	
	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
			ret = item->data->PreUpdate(dt);
		item = item->next;
	}

	item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
  			ret = item->data->Update(dt);
		item = item->next;
	}

	item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
			ret = item->data->PostUpdate(dt);
		item = item->next;
	}

	FinishUpdate();
	return ret;
}

// ------------------------------------------------------------
bool Application::CleanUp()
{
	bool ret = true;
	p2List_item<Module*>* item = list_modules.getLast();

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}
	return ret;
}

// ------------------------------------------------------------
void Application::AddModule(Module* mod)
{
	list_modules.add(mod);
}

// ------------------------------------------------------------
const char* Application::GetTitle() const
{
	return title.c_str();
}

// ------------------------------------------------------------
const char* Application::GetOrganizationName() const
{
	return organization.c_str();
}

// ------------------------------------------------------------
void Application::ExecuteBrowser(const char* path)
{
	ShellExecute(NULL, "open", path, NULL, NULL, SW_SHOWDEFAULT);
}