#include "Application.h"
#include "ModuleLoadMesh.h"
#include "GameObject.h"
#include "ModuleGOManager.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"
#include "MathGeoLib\src\MathGeoLib.h"
#include "Glew\include\glew.h"

#include "Assimp\include\cimport.h"
#include "Assimp\include\scene.h"
#include "Assimp\include\postprocess.h"
#include "Assimp\include\cfileio.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")

#include "Devil/include/il.h"
#include "Devil/include/ilut.h"
#pragma comment ( lib, "Devil/libx86/DevIL.lib" )
#pragma comment ( lib, "Devil/libx86/ILU.lib" )
#pragma comment ( lib, "Devil/libx86/ILUT.lib" )

#pragma comment (lib, "Assimp/libx86/assimp.lib")
#pragma comment (lib, "Glew/libx86/glew32.lib")

using namespace std;


ModuleLoadMesh::ModuleLoadMesh(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleLoadMesh::~ModuleLoadMesh()
{}

bool ModuleLoadMesh::Init()
{
	ilInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
	
	return true;
}

bool ModuleLoadMesh::CleanUp()
{
	return true;
}

vector<GameObject*> ModuleLoadMesh::LoadFile(const char* path)
{
	vector<GameObject*> go_list;

	// Start from aiScene::mRootNode then go recursive from there.
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		aiNode* parent_node = scene->mRootNode;

		GameObject* parent_go = App->go_manager->CreateNewGO(nullptr);
		parent_go->name = parent_node->mName.C_Str();
		go_list.push_back(parent_go);

		// Then loop aiNode::mNumChildren
		for (int i = 0; i < parent_node->mNumChildren; ++i)
		{
			// ... then deal with each aiNode::mChildren[n]
			GameObject* child_go = LoadMesh(scene, parent_node->mChildren[i], parent_go, path);
			go_list.push_back(child_go);
		}

		aiReleaseImport(scene);
	}

	return go_list;
}

GameObject* ModuleLoadMesh::LoadMesh(const aiScene* scene, aiNode* child_node, GameObject* parent, const char* path)
{
	GameObject* child_go = App->go_manager->CreateNewGO(parent);
	child_go->name = child_node->mName.C_Str();

	if (child_node->mNumMeshes <= 0)
	{
		// Get transformations --------------------------
		aiVector3D trans;
		aiQuaternion rot;
		aiVector3D sca;

		child_node->mTransformation.Decompose(sca, rot, trans);

		float3 position(trans.x, trans.y, trans.z);
		Quat rot_quat(rot.x, rot.y, rot.z, rot.w);
		float3 scale(sca.x, sca.y, sca.z);

		// Add ComponentTransform -->
		ComponentTransform* trans_comp = (ComponentTransform*)child_go->AddComponent(TRANSFORM);
		trans_comp->SetPosition(position);
		trans_comp->SetRotationQuat(rot_quat);
		trans_comp->SetScale(scale);
	}
	else
	{
		for (int i = 0; i < child_node->mNumMeshes; i++)
		{
			aiMesh* new_mesh = scene->mMeshes[child_node->mMeshes[i]];
			MeshData m = MeshData();

			// copy vertices ------------------------------------
			m.num_vertices = new_mesh->mNumVertices;
			m.vertices = new uint[m.num_vertices * 3];
			memcpy(m.vertices, new_mesh->mVertices, sizeof(float)*m.num_vertices * 3);
			LOG("New m with %d vertices", m.num_vertices);

			// Create vertice buffer
			glGenBuffers(1, (GLuint*)&(m.id_vertices));
			glBindBuffer(GL_ARRAY_BUFFER, m.id_vertices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * m.num_vertices, m.vertices, GL_STATIC_DRAW);

			// copy indices -------------------------------------
			// copy faces 
			if (new_mesh->HasFaces())
			{
				m.num_indices = new_mesh->mNumFaces * 3;
				m.indices = new uint[m.num_indices];
				for (uint j = 0; j < new_mesh->mNumFaces; j++)
				{
					if (new_mesh->mFaces[j].mNumIndices == 3)
					{
						memcpy(&m.indices[j * 3], new_mesh->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}

				// Create indices buffer
				glGenBuffers(1, (GLuint*)&(m.id_indices));
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.id_indices);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * m.num_indices, m.indices, GL_STATIC_DRAW);
			}

			// copy UVS ------------------------------------- 
			if (new_mesh->HasTextureCoords(m.id_uvs))
			{
				m.num_uvs = new_mesh->mNumVertices;
				m.uvs = new float[m.num_uvs * 2];

				for (int i = 0; i < new_mesh->mNumVertices; ++i)
				{
					memcpy(&m.uvs[i * 2], &new_mesh->mTextureCoords[0][i].x, sizeof(float));
					memcpy(&m.uvs[(i * 2) + 1], &new_mesh->mTextureCoords[0][i].y, sizeof(float));
				}

				// Create UVS buffer
				glGenBuffers(1, (GLuint*)&(m.id_uvs));
				glBindBuffer(GL_ARRAY_BUFFER, m.id_uvs);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * m.num_uvs, m.uvs, GL_STATIC_DRAW);
			}

			// copy normals -------------------------------------
			if (new_mesh->HasNormals())
			{
				m.num_normals = new_mesh->mNumVertices;
				m.normals = new float[m.num_normals * 3];
				memcpy(m.normals, new_mesh->mNormals, sizeof(float) * m.num_normals * 3);
				LOG("New m with %d normals", m.num_normals);

				// Create normals buffer
				glGenBuffers(1, (GLuint*)&(m.id_normals));
				glBindBuffer(GL_ARRAY_BUFFER, m.id_normals);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * m.num_normals, m.normals, GL_STATIC_DRAW);
			}

			// Generate bbox --------------------------------
			m.bbox_mesh.SetNegativeInfinity();
			m.bbox_mesh.Enclose((float3*)m.vertices, m.num_vertices);

			// Get transformations --------------------------
			aiVector3D trans;
			aiVector3D sca;
			aiQuaternion rot;

			child_node->mTransformation.Decompose(sca, rot, trans);

			float3 position(trans.x, trans.y, trans.z);
			float3 scale(sca.x, sca.y, sca.z);
			Quat rot_quat(rot.x, rot.y, rot.z, rot.w);
			
			// Add ComponentTransform -->
			ComponentTransform* trans_comp = (ComponentTransform*)child_go->AddComponent(TRANSFORM);
			trans_comp->SetPosition(position);
			trans_comp->SetRotationQuat(rot_quat);
			trans_comp->SetScale(scale);

			// Add ComponentMesh -->
			ComponentMesh* mesh_comp = (ComponentMesh*)child_go->AddComponent(MESH);
			mesh_comp->SetMesh(m);

			if (scene->HasMaterials())
			{
				aiMaterial* material = scene->mMaterials[new_mesh->mMaterialIndex];

				if (material != nullptr)
				{
					aiString new_path;

					material->GetTexture(aiTextureType_DIFFUSE, 0, &new_path);

					if (new_path.length > 0)
					{
						std::string texture_path = "../Game/Library/Textures/";
						std::string real_path = new_path.data;

						real_path.erase(0, real_path.find_last_of("\\") + 1);
						texture_path += real_path;

						ComponentMaterial* mat_comp = (ComponentMaterial*)child_go->AddComponent(MATERIAL);
						mat_comp->name_id = LoadTexture(texture_path.c_str());

						real_path.clear();
						texture_path.clear();
					}
				}
			}			
		}
	}

	for (int i = 0; i < child_node->mNumChildren; i++)
	{
		LoadMesh(scene, child_node->mChildren[i], child_go, path);
	}

	return child_go;
}

uint ModuleLoadMesh::LoadTexture(const char* path)
{
	ILuint id;
	ilGenImages(1, &id);
	ilBindImage(id);
	ilLoadImage(path);

	return ilutGLBindTexImage();
}