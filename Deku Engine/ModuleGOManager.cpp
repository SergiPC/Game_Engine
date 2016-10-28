#include "ModuleGOManager.h"
#include "GameObject.h"

using namespace std;

ModuleGOManager::ModuleGOManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleGOManager::~ModuleGOManager()
{}

// -----------------------------------------------------------------
bool ModuleGOManager::Init()
{
	LOG("Setting up GOManager");

	root = new GameObject(nullptr);
	root->name = "Root";

	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
update_status ModuleGOManager::Update(float dt)
{
	root->Update();

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
bool ModuleGOManager::CleanUp()
{
	// root ----------
	root->CleanUp();
	RELEASE(root);

	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
GameObject* ModuleGOManager::CreateNewGO(GameObject* parent)
{
	if (parent == nullptr)
		parent = root;

	// Create new GameObject -----
	GameObject* new_go;

	new_go = new GameObject(parent);
	parent->children.push_back(new_go);

	// Create name
	new_go->name += to_string(index);
	index++;

	return new_go;
}

// -----------------------------------------------------------------
bool ModuleGOManager::DeleteGO(GameObject* go)
{
	return go->parent->DeleteChild(go);
}