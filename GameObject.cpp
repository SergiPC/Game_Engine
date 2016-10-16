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
void GameObject::SetName(const char* new_name)
{
	name = new_name;
}

// -----------------------------------------------------------------
Component* GameObject::AddComponent(Type TIPE)
{
	Component* new_component = nullptr;

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
void GameObject::DelComponent(Component* comp)
{
	comp->CleanUp();
}

// I need to limit the number of components ------------------------
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
/*
// -----------------------------------------------------------------
ComponentTransform* GameObject::AddTransform()
{
	ComponentTransform* new_trans = new ComponentTransform(this);

	components.push_back(new_trans);

	return new_trans;
}

// -----------------------------------------------------------------
ComponentMesh* GameObject::AddMesh(MeshData _mesh)
{
	ComponentMesh* new_mesh = new ComponentMesh(this, _mesh);

	components.push_back(new_mesh);

	return new_mesh;
}

// -----------------------------------------------------------------
ComponentMaterial* GameObject::AddMaterial(size_t _name_id)
{
	ComponentMaterial* new_material = new ComponentMaterial(this, _name_id);

	components.push_back(new_material);

	return new_material;
}
*/
// -----------------------------------------------------------------
void GameObject::Translate(float3 new_pos)
{
	position = new_pos;
}

// -----------------------------------------------------------------
void GameObject::Rotate(float3 new_euler)
{
	euler_rotation = new_euler;
}

// -----------------------------------------------------------------
void GameObject::Rotate(Quat new_quat)
{
	quat_rotation = new_quat;
}

// -----------------------------------------------------------------
void GameObject::Scale(float3 new_scale)
{
	scale = new_scale;
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