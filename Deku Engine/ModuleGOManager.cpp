#include "ModuleGOManager.h"
#include "GameObject.h"
#include "Component.h"
#include "Imgui\imgui.h"
#include <vector>
#include <string>
using namespace std;

ModuleGOManager::ModuleGOManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleGOManager::~ModuleGOManager()
{}

// -----------------------------------------------------------------
bool ModuleGOManager::Init()
{
	root = new GameObject(nullptr);
	return true;
}

// -----------------------------------------------------------------
bool ModuleGOManager::CleanUp()
{
	root->CleanUp();
	RELEASE(root);
	return true;
}

// -----------------------------------------------------------------
update_status ModuleGOManager::Update(float dt)
{
	root->Update();

	//HierarchyPanel();
	//InspectorPanel();
	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
GameObject* ModuleGOManager::AddGameObject(GameObject* parent)
{
	if (parent == nullptr)
		parent = root;

	GameObject* object;

	object = new GameObject(parent);
	parent->children.push_back(object);
	numObjects++;
	object->name += std::to_string(numObjects);

	return object;
}

// -----------------------------------------------------------------
bool ModuleGOManager::RemoveGameObject(GameObject* go)
{
	numObjects--;
	return go->root->RemoveChild(go);
}
/*
// -----------------------------------------------------------------
void ModuleGOManager::HierarchyPanel()
{
	ImGui::Begin("Hierarchy");

	for (vector<GameObject*>::iterator item = root->children.begin(); item != root->children.end(); ++item)
		HierarchyShowChilds(*item);

	ImGui::End();
}

// -----------------------------------------------------------------
void ModuleGOManager::HierarchyShowChilds(GameObject* gameObject)
{
		uint flag = 0;

		if (focusGo == gameObject)
			flag |= ImGuiTreeNodeFlags_Selected;

		if (gameObject->children.size() == 0)
			flag |= ImGuiTreeNodeFlags_Bullet;

		if (ImGui::TreeNodeEx(gameObject->name.data(), flag))
		{
			if (ImGui::IsItemClicked(0))
			{
				focusGo = gameObject;
			}

			for (vector<GameObject*>::iterator item = gameObject->children.begin(); item != gameObject->children.end(); ++item)
				HierarchyShowChilds(*item);

			ImGui::TreePop();
		}
}

// -----------------------------------------------------------------
void ModuleGOManager::InspectorPanel() 
{
	ImGui::Begin("Inspector");

	if (focusGo != nullptr)
	{
		for (vector<Component*>::iterator item = focusGo->components.begin(); item != focusGo->components.end(); ++item)
			(*item)->OnEditor();
	}

	ImGui::End();
}
*/