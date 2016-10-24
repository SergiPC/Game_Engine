#include "GameObject.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"
#include "Math.h"
using namespace std;

GameObject::GameObject()
{
	root = nullptr;
	name.resize(20);
	name = "GameObject";
}

GameObject::GameObject(GameObject* parent)
{
	root = parent;
	name.resize(20);
	name = "GameObject";
}

GameObject::~GameObject()
{
	root = nullptr;
}

// -----------------------------------------------------------------
bool GameObject::CleanUp()
{
	for (vector<GameObject*>::iterator item = children.begin(); item != children.end(); ++item)
	{
		(*item)->CleanUp();
		RELEASE(*item);
	}
	children.clear();

	for (vector<Component*>::iterator item = components.begin(); item != components.end(); ++item)
	{
		RELEASE(*item);	
	}
	components.clear();

	return true;
}

// -----------------------------------------------------------------
bool GameObject::Start()
{
	return true;
}

// -----------------------------------------------------------------
bool GameObject::Update()
{
	bool ret = true;

	//Call each Component Update
	for (vector<Component*>::iterator item = components.begin(); item != components.end(); ++item)
	{
		(*item)->Update();
	}

	//Call each Child Update
	for (vector<GameObject*>::iterator item = children.begin(); item != children.end(); ++item)
	{
		(*item)->Update();
	}

	return ret;
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
Component* GameObject::AddComponent(componentType _type)
{
	Component* component = NULL;
	//Check there are no duplicate components
	component = GetComponent(_type);
	if (component != nullptr)
		return component;

	switch (_type)
	{
		case Transform: component = new ComponentTransform(this); 
			break;

		case Meshes: component = new ComponentMesh(this);
			break;

		case Material: component = new ComponentMaterial(this);
			break;

		default: component = new ComponentTransform(this); 
			break;
	}

	components.push_back(component);
	return component;
}

// -----------------------------------------------------------------
Component* GameObject::GetComponent(componentType _type)
{

	Component* component = NULL;

	for (vector<Component*>::iterator item = components.begin(); item != components.end(); ++item)
	{
		if ((*item)->type == _type)
		{
			component = (*item);
			break;
		}
	}

	return component;
}

// -----------------------------------------------------------------
bool GameObject::RemoveChild(GameObject* child)
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
void GameObject::GenerateBoundingBox(uint* vertices,uint numVertices)
{
	gBox.SetNegativeInfinity();
	gBox.Enclose((float3*)vertices, numVertices);
}