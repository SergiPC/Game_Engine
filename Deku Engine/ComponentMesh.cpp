#include "Globals.h"
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

	if (enabled)
	{
		ComponentTransform* new_trans = (ComponentTransform*)owner->GetComponent(TRANSFORM);
		ComponentMaterial* new_mat = (ComponentMaterial*)owner->GetComponent(MATERIAL);

		if (new_mat == nullptr)
			App->renderer3D->RenderMesh(mesh, new_trans->GetWorldTransform(), 0, false);

		else
			App->renderer3D->RenderMesh(mesh, new_trans->GetWorldTransform(), new_mat->name_id, new_mat->IsEnable());

		// Render bounding box -------
		if (owner->BBoxIsEnable())
			owner->BBoxDebug();
	}

	return ret;
}

// -----------------------------------------------------------------
void ComponentMesh::OnEditor()
{
	if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
	{
		bool comp_enable = enabled;

		if (ImGui::Checkbox("##Mesh", &comp_enable))
			enabled = comp_enable;

		ImGui::SameLine();
		(enabled) ? (ImGui::Text("(Active)")) : (ImGui::Text("(Desactivated)"));

		ImGui::Separator();	// -------

		// Bounding Box ------------------------
		bool aabb_enable = owner->BBoxIsEnable();

		if (ImGui::Checkbox("##Bounding Box", &aabb_enable))
			owner->BBoxSetEnable(aabb_enable);

		ImGui::SameLine();

		if (aabb_enable)
			ImGui::TextColored(ImVec4(0.25f, 0.88f, 0.81f, 0.70f), "Bounding Box (Active)");
		else
			ImGui::TextColored(ImVec4(0.25f, 0.88f, 0.81f, 0.40f), "Bounding Box (Desactivated)");

		ImGui::Separator();	// -------

		int numTriangles = mesh.num_indices/3;

		ImGui::Text("Triangles:"); ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.25f, 0.88f, 0.81f, 0.70f), "%d", numTriangles);

		ImGui::Text("Vertices:"); ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.25f, 0.88f, 0.81f, 0.70f), "%d", mesh.num_vertices);

		ImGui::Text("Indices:"); ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.25f, 0.88f, 0.81f, 0.70f), "%d", mesh.num_indices);
	}
}

// -----------------------------------------------------------------
void ComponentMesh::SetMesh(MeshData new_mesh)
{
	mesh = new_mesh;
	owner->GenerateBBox(mesh.vertices, mesh.num_vertices);
}