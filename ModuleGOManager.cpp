#include "Application.h"
#include "ModuleGOManager.h"

using namespace std;

ModuleGOManager::ModuleGOManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleGOManager::~ModuleGOManager()
{}

// -----------------------------------------------------------------
bool ModuleGOManager::Start()
{
	LOG("Setting up GOManager");

	root = new GameObject();
	game_objects_list.push_back(root);
	root->SetName("Hierarchy");

	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleGOManager::CleanUp()
{
	LOG("Cleaning GOManager");

	return true;
}

// -----------------------------------------------------------------
update_status ModuleGOManager::Update(float dt)
{

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
GameObject* ModuleGOManager::CreateNewGO(GameObject* parent)
{
	if (parent == nullptr)
		parent = root;

	// If else shortcut <-- Must known
	//(parent == nullptr) ? (parent = root) : (parent == nullptr);

	GameObject* new_go = new GameObject(parent);
	game_objects_list.push_back(new_go);

	return new_go;
}

// -----------------------------------------------------------------
void ModuleGOManager::DeleteGO(GameObject* go)
{
	go->CleanUp();
}

// -----------------------------------------------------------------
GameObject* ModuleGOManager::DuplicateGO(GameObject* go)
{
	GameObject* copy_go = new GameObject();
	copy_go = go;

	return copy_go;
}

GameObject* ModuleGOManager::GetParent()
{
	return root;
}

// -----------------------------------------------------------------
void ModuleGOManager::SetParent(GameObject* go, GameObject* parent)
{
	go->SetParent(parent);
}

// -----------------------------------------------------------------
std::vector<GameObject*> ModuleGOManager::GetGOVector()
{
	return game_objects_list;
}