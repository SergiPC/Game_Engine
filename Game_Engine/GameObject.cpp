#include "GameObject.h"
#include "Globals.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"
#include "ModuleLoadMesh.h"

#include <sstream>

class ModuleGOManager;

using namespace std;

GameObject::GameObject(GameObject* _parent, const char* _name) : name(_name)
{
	parent = _parent;
	name.resize(20);

	if (parent)
		parent->children.push_back(this);
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
void GameObject::Update()
{
	vector<Component*>::iterator tmp_comp = components.begin();

	while (tmp_comp != components.end())
	{
		(*tmp_comp)->Update();
		tmp_comp++;
	}

	vector<GameObject*>::iterator tmp_go = children.begin();

	while (tmp_go != children.end())
	{
		(*tmp_go)->Update();
		tmp_go++;
	}
}

// -----------------------------------------------------------------
bool GameObject::CleanUp()
{
	LOG("Cleaning GameObject");

	vector<Component*>::iterator tmp_comp = components.begin();

	while (tmp_comp != components.end())
	{
		RELEASE(*tmp_comp);
		tmp_comp++;
	}

	vector<GameObject*>::iterator tmp_go = children.begin();

	while (tmp_go != children.end())
	{
		(*tmp_go)->CleanUp();
		RELEASE(*tmp_go);
		tmp_go++;
	}

	return true;
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

// -----------------------------------------------------------------
Component* GameObject::AddComponent(Type TIPE)
{
	Component* new_component = nullptr;

	// We can't add two components with the same type
	new_component = GetComponent(TIPE);

	if (new_component != nullptr)
		return new_component;

	switch (TIPE)
	{
	case TRANSFORM: new_component = new ComponentTransform(this);
		break;

	case MESH: new_component = new ComponentMesh(this);
		break;

	case MATERIAL: new_component = new ComponentMaterial(this);
		break;
	}

	components.push_back(new_component);
	
	return new_component;
}

// -----------------------------------------------------------------
Component* GameObject::GetComponent(Type TIPE)
{
	Component* new_component = nullptr;

	for (vector<Component*>::iterator comp_it = components.begin(); comp_it != components.end(); ++comp_it)
	{
		if ((*comp_it)->GetType() == TIPE)
		{
			new_component = (*comp_it);
			break;
		}
	}

	return new_component;
}

// -----------------------------------------------------------------
void GameObject::DelComponent(Component* comp)
{
	comp->CleanUp();
}

// -----------------------------------------------------------------
void GameObject::DelChild(GameObject* go_child)
{
	bool ret = false;

	for (vector<GameObject*>::iterator item = children.begin(); item != children.end(); ++item)
	{
		if ((*item) == go_child)
		{
			children.erase(item);
			go_child->CleanUp();
			RELEASE(go_child);
			ret = true;
		}
	}
}

// -----------------------------------------------------------------
GameObject* GameObject::GetParent()
{
	return parent;
}

// -----------------------------------------------------------------
void GameObject::SetParent(GameObject* new_parent)
{
	parent = new_parent;
}