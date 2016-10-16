#include "Globals.h"
#include "Application.h"
#include "ComponentMesh.h"
#include "ModuleLoadMesh.h"
#include "GameObject.h"
#include "Component.h"
#include "OpenGL.h"
#include "Imgui\imgui.h"

// -----------------------------------------------------------------
ComponentMesh::ComponentMesh(GameObject* _parent) : Component(_parent, MESH)
{
	MeshData new_mesh;
	mesh = new_mesh;
}

// -----------------------------------------------------------------
ComponentMesh::~ComponentMesh()
{}

// -----------------------------------------------------------------
void ComponentMesh::Update()
{
	float4x4 matrix;

	ComponentTransform* new_trans = (ComponentTransform*)GetParent()->GetComponent(TRANSFORM);
	matrix = new_trans->GetLocalTransform();

	if (new_trans == nullptr)
		matrix = float4x4::identity;

	uint id;

	ComponentMaterial* new_mat = (ComponentMaterial*)GetParent()->GetComponent(MESH);
	id = new_mat->name_id;

	if (new_mat == nullptr)
		id = 0;

	App->renderer3D->DrawMesh(mesh, matrix, id);
}

// -----------------------------------------------------------------
void ComponentMesh::SetMesh(MeshData new_mesh)
{
	mesh = new_mesh;
}