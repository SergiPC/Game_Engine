#include "Application.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"

using namespace std;

// -----------------------------------------------------------------
GameObject::GameObject(GameObject* parent) : enabled(true), bbox_enabled(true)
{
	this->parent = parent;
	name = "GameObject";

	// Create new Component Transform
	AddComponent(TRANSFORM);
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

	if (enabled)
	{
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
bool GameObject::IsEnable() const
{
	return enabled;
}

// -----------------------------------------------------------------
void GameObject::SetEnable(bool enable)
{
	if (enabled != enable)
		enabled = enable;
}

// -----------------------------------------------------------------
bool GameObject::DeleteChild(GameObject* child)
{
	bool ret = false;

	for (vector<GameObject*>::iterator child_it = children.begin(); child_it != children.end(); ++child_it)
	{
		if ((*child_it) == child)
		{
			children.erase(child_it);
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

// Read only -------------------------------------------------------
const AABB GameObject::GetBBox()
{
	return bbox_go;
}

// -----------------------------------------------------------------
void GameObject::GenerateBBox(uint* vertices, uint num_vertices)
{
	bbox_go.SetNegativeInfinity();
	bbox_go.Enclose((float3*)vertices, num_vertices);

	tmp_bbox_go = bbox_go;
}

// Scale doesn't work well -----------------------------------------
void GameObject::UpdateBBox(float4x4 world_trans)
{
	tmp_obb = bbox_go.Transform(world_trans);
	tmp_bbox_go = tmp_obb.MinimalEnclosingAABB();
}

// Read only -------------------------------------------------------
const bool GameObject::BBoxIsEnable() const
{
	return bbox_enabled;
}

// -----------------------------------------------------------------
void GameObject::BBoxSetEnable(bool enable)
{
	if (bbox_enabled != enable)
		bbox_enabled = enable;
}

// -----------------------------------------------------------------
void GameObject::BBoxDebug()
{
	App->renderer3D->RenderBBoxDebug(tmp_bbox_go);
}