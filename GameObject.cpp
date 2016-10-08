#include "GameObject.h"
#include "ModuleGOManager.h"
#include "Globals.h"

#include <sstream>

using namespace std;

GameObject::GameObject(GameObject* root = nullptr)
{
	parent = root;
	name = "NewGameObject";

	CheckName(name.c_str);
	// Set name with number ?
	// Check if there is any other GameObject with that name:
	ostringstream new_name;
	new_name << name << index;
	name = new_name.str();
	index++;
}

GameObject::~GameObject()
{}

// -----------------------------------------------------------------
bool GameObject::Start()
{

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
Component* GameObject::AddComponents(Component* type)
{

}

// -----------------------------------------------------------------
void GameObject::DelComponent(Component* comp)
{

}

// -----------------------------------------------------------------
Component* GameObject::FindComponent(Type type)
{

}

// -----------------------------------------------------------------
vector<Component*> GameObject::FindComponentsVec(Type type)
{

}

// -----------------------------------------------------------------
GameObject* GameObject::GetParent()
{
	return parent;
}

// -----------------------------------------------------------------
void GameObject::SetName(const char* new_name)
{

}

// -----------------------------------------------------------------
const char* GameObject::CheckName(const char* new_name)
{
	GetGOVector();
}

// -----------------------------------------------------------------
void GameObject::SetParent(GameObject* new_parent)
{
	parent = new_parent;
}

// -----------------------------------------------------------------
bool GameObject::IsEnable()
{

}

// -----------------------------------------------------------------
void GameObject::SetEnable(bool enable)
{

}