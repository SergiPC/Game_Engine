#include "GameObject.h"
#include "Globals.h"

#include <sstream>

using namespace std;

GameObject::GameObject(GameObject* root)
{
	parent = root;
	name = "Game Object";

	//CheckName(name.c_str);
	// Set name with number ?
	// Check if there is any other GameObject with that name:
}

GameObject::~GameObject()
{}

// -----------------------------------------------------------------
bool GameObject::Start()
{
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
void GameObject::Update(float dt)
{

}

// -----------------------------------------------------------------
bool GameObject::CleanUp()
{
	LOG("Cleaning GameObject");

	return true;
}

// -----------------------------------------------------------------
Component* GameObject::AddComponents(Type TIPE)
{
	Component* new_component;

	if (TIPE == TRANSFORM)
		new_component = new Transform();

	components.push_back(new_component);
	
	return new_component;
}

// -----------------------------------------------------------------
void GameObject::DelComponent(Component* comp)
{
	comp->CleanUp();
}

// -----------------------------------------------------------------
Component* GameObject::FindComponent(Type TIPE)
{
	int i = 0;

	while (components[i] != nullptr)
	{
		if (components[i]->GetType() == TIPE)
		{
			return components[i];
		}
		i++;
	}

	return nullptr;
}

// -----------------------------------------------------------------
//vector<Component*> GameObject::FindComponentsVec(Type TIPE)
//{}

// -----------------------------------------------------------------
GameObject* GameObject::GetParent()
{
	return parent;
}

// -----------------------------------------------------------------
void GameObject::SetName(const char* new_name)
{
	name = new_name;
}

// -----------------------------------------------------------------
//const char* GameObject::CheckName(const char* new_name)
//{}

// -----------------------------------------------------------------
void GameObject::SetParent(GameObject* new_parent)
{
	parent = new_parent;
}

// -----------------------------------------------------------------
bool GameObject::IsEnable()
{
	return enabled;
}

// -----------------------------------------------------------------
void GameObject::SetEnable(bool enable)
{
	enabled = enable;
}