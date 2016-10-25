#include "GameObject.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"

using namespace std;

// -----------------------------------------------------------------
GameObject::GameObject(GameObject* parent) : enabled(true)
{
	this->parent = parent;
	name = "GameObject";
}

// -----------------------------------------------------------------
GameObject::~GameObject()
{
	parent = nullptr;
}

// -----------------------------------------------------------------
bool GameObject::Start()
{
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool GameObject::Update()
{
	bool ret = true;

	// Update all components -----
	vector<Component*>::iterator tmp_comp = components.begin();

	while (tmp_comp != components.end())
	{
		(*tmp_comp)->Update();
		tmp_comp++;
	}

	// Update all children -------
	vector<GameObject*>::iterator tmp_go = children.begin();

	while (tmp_go != children.end())
	{
		(*tmp_go)->Update();
		tmp_go++;
	}

	return ret;
}

// -----------------------------------------------------------------
bool GameObject::CleanUp()
{
	LOG("Cleaning GameObject");

	// CleanUp all components ----
	vector<Component*>::iterator tmp_comp = components.begin();

	while (tmp_comp != components.end())
	{
		RELEASE(*tmp_comp);
		tmp_comp++;
	}

	components.clear();

	// CleanUp all children ------
	vector<GameObject*>::iterator tmp_go = children.begin();

	while (tmp_go != children.end())
	{
		(*tmp_go)->CleanUp();
		RELEASE(*tmp_go);
		tmp_go++;
	}

	children.clear();

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

	// If enable == false ----> put all components & children == false
}

// -----------------------------------------------------------------
bool GameObject::DeleteChild(GameObject* child)
{
	bool ret = false;

	for (vector<GameObject*>::iterator item = children.begin(); item != children.end(); ++item)
	{
		if ((*item) == child)
		{
			children.erase(item);
			child->CleanUp();
			RELEASE(child);
			ret = true;
		}
	}

	return ret;
}

// -----------------------------------------------------------------
Component* GameObject::AddComponent(Type type)
{
	Component* new_component = NULL;

	// For now, we can't add two components with the same type
	new_component = GetComponent(type);

	if (new_component != nullptr)
		return new_component;

	switch (type)
	{
		case TRANSFORM: new_component = new ComponentTransform(this); 
			break;

		case MESH: new_component = new ComponentMesh(this);
			break;

		case MATERIAL: new_component = new ComponentMaterial(this);
			break;

		default: new_component = new ComponentTransform(this); 
			break;
	}

	components.push_back(new_component);

	return new_component;
}

// -----------------------------------------------------------------
Component* GameObject::GetComponent(Type type)
{

	Component* new_component = nullptr;

	for (vector<Component*>::iterator comp_it = components.begin(); comp_it != components.end(); ++comp_it)
	{
		if ((*comp_it)->GetType() == type)
		{
			new_component = (*comp_it);
			break;
		}
	}

	return new_component;
}

// -----------------------------------------------------------------
void GameObject::DeleteComponent(Component* comp)
{
	//comp->CleanUp();
}

// -----------------------------------------------------------------
void GameObject::GenerateBoundingBox(uint* vertices,uint numVertices)
{
	gBox.SetNegativeInfinity();
	gBox.Enclose((float3*)vertices, numVertices);
}