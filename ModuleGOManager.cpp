#include "Globals.h"
#include "Application.h"
#include "ModuleGOManager.h"
#include "GameObject.h"

using namespace std;

ModuleGOManager::ModuleGOManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleGOManager::~ModuleGOManager()
{}

// -----------------------------------------------------------------
bool ModuleGOManager::Start()
{
	LOG("Setting up GOManager");

	root = new GameObject(nullptr, "Root");
	root->SetName("Root");

	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleGOManager::CleanUp()
{
	LOG("Cleaning GOManager");

	// root ----------
	root->CleanUp();
	RELEASE(root);

	return true;
}

// -----------------------------------------------------------------
update_status ModuleGOManager::Update(float dt)
{
	root->Update();

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
GameObject* ModuleGOManager::CreateNewGO(GameObject* _parent)
{
	if (_parent == nullptr)
		_parent = root;

	// Create name
	string text = "GameObject ";
	text += to_string(index);
	name = text;
	index++;

	GameObject* new_go = new GameObject(_parent, name.data());

	return new_go;
}

// -----------------------------------------------------------------
void ModuleGOManager::DeleteGO(GameObject* go)
{
	go->CleanUp();
}

// -----------------------------------------------------------------
GameObject* ModuleGOManager::GetRoot()
{
	return root;
}