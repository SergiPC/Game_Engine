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

// -----------------------------------------------------------------
void ComponentMesh::OnEditor()
{
	if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
	{
		int num_triangles = mesh.num_indices / 3;

		ImGui::Text("Triangles:"); ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.25f, 0.88f, 0.81f, 0.70f), "%d", num_triangles);

		ImGui::Text("Vertices:"); ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.25f, 0.88f, 0.81f, 0.70f), "%d", mesh.num_vertices);

		ImGui::Text("Indices:"); ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.25f, 0.88f, 0.81f, 0.70f), "%d", mesh.num_indices);
	}
}