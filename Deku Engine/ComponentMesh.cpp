#include "ComponentMesh.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ComponentTransform.h"
#include "ComponentMaterial.h"
#include "GameObject.h"
#include "MathGeoLib\src\MathGeoLib.h"
#include "Imgui\imgui.h"

using namespace std;

// -----------------------------------------------------------------
ComponentMesh::ComponentMesh(GameObject* owner) : Component(owner, MESH)
{
	MeshData new_mesh;
	mesh = new_mesh;	
}

// -----------------------------------------------------------------
ComponentMesh::~ComponentMesh()
{}

// -----------------------------------------------------------------
bool ComponentMesh::Update()
{
	bool ret = true;

	ComponentTransform* new_trans = (ComponentTransform*)owner->GetComponent(TRANSFORM);
	ComponentMaterial* new_mat = (ComponentMaterial*)owner->GetComponent(MATERIAL);

	if (new_trans == nullptr && new_mat == nullptr)
		App->renderer3D->RenderMesh(mesh, math::float4x4::identity, 0);

	else if(new_mat == nullptr)
		App->renderer3D->RenderMesh(mesh, new_trans->GetWorldTransform(), 0);

	else if (new_trans == nullptr)
		App->renderer3D->RenderMesh(mesh, math::float4x4::identity, new_mat->name_id);

	else
		App->renderer3D->RenderMesh(mesh, new_trans->GetWorldTransform(), new_mat->name_id);

	return ret;
}

// -----------------------------------------------------------------
void ComponentMesh::OnEditor()
{
	if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
	{
		bool comp_enable = this->enabled;

		if (ImGui::Checkbox("", &comp_enable))
			this->enabled = comp_enable;

		ImGui::SameLine();  ImGui::Text("Active");

		ImGui::Separator();	// -------

		int numTriangles = mesh.numIndices/3;

		ImGui::Text("Triangles:"); ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.25f, 0.88f, 0.81f, 0.70f), "%d", numTriangles);

		ImGui::Text("Vertices:"); ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.25f, 0.88f, 0.81f, 0.70f), "%d", mesh.numVertices);

		ImGui::Text("Indices:"); ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.25f, 0.88f, 0.81f, 0.70f), "%d", mesh.numIndices);
	}
}

// -----------------------------------------------------------------
bool ComponentMesh::SetMesh(MeshData new_mesh)
{
	mesh = new_mesh;
	//owner->GenerateBoundingBox(mesh.vertices, Cmesh.numVertices);
	return true;
}