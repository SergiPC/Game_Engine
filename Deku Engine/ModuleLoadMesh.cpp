#include "Application.h"
#include "ModuleLoadMesh.h"
#include "GameObject.h"
#include "ModuleGOManager.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"
#include "MathGeoLib\src/MathGeoLib.h"
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

vector<GameObject*> ModuleLoadMesh::Load(const char* path)
{
	vector<GameObject*> gameObjects;

	// Start from aiScene::mRootNode then go recursive from there.
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		aiNode* rootNode = scene->mRootNode;

		GameObject* parent = App->go_manager->AddGameObject(nullptr);
		parent->name = rootNode->mName.C_Str();
		gameObjects.push_back(parent);

		// Then loop aiNode::mNumChildren
		for (int i = 0; i < rootNode->mNumChildren; ++i)
		{
			// ... then deal with each aiNode::mChildren[n]
			GameObject* child = LoadMesh(scene, rootNode->mChildren[i], path, parent);
			gameObjects.push_back(child);
		}

		aiReleaseImport(scene);
	}

	return gameObjects;
}

GameObject* ModuleLoadMesh::LoadMesh(const aiScene* scene, aiNode* node, const char* path, GameObject* parent)
{
	GameObject* child = App->go_manager->AddGameObject(parent);
	child->name = node->mName.C_Str();

	if (node->mNumMeshes <= 0)
	{
		// Get transformations --------------------------
		aiVector3D translation;
		aiVector3D scaling;
		aiQuaternion rotation;

		node->mTransformation.Decompose(scaling, rotation, translation);

		float3 position(translation.x, translation.y, translation.z);
		float3 scale(scaling.x, scaling.y, scaling.z);
		Quat _rotation(rotation.x, rotation.y, rotation.z, rotation.w);

		// Add ComponentTransform -->
		ComponentTransform* Ctransform = (ComponentTransform*)child->AddComponent(Transform);
		Ctransform->SetPosition(position);
		Ctransform->SetRotationQuat(_rotation);
		Ctransform->SetScale(scale);
	}
	else
	{
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* aimesh = scene->mMeshes[node->mMeshes[i]];
			MeshT mesh = MeshT();

			// copy vertices ------------------------------------
			mesh.numVertices = aimesh->mNumVertices;
			mesh.vertices = new uint[mesh.numVertices * 3];
			memcpy(mesh.vertices, aimesh->mVertices, sizeof(float)*mesh.numVertices * 3);
			LOG("New mesh with %d vertices", mesh.numVertices);

			// Create vertice buffer
			glGenBuffers(1, (GLuint*)&(mesh.idVertices));
			glBindBuffer(GL_ARRAY_BUFFER, mesh.idVertices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * mesh.numVertices, mesh.vertices, GL_STATIC_DRAW);

			// copy indices -------------------------------------
			// copy faces 
			if (aimesh->HasFaces())
			{
				mesh.numIndices = aimesh->mNumFaces * 3;
				mesh.indices = new uint[mesh.numIndices];
				for (uint j = 0; j < aimesh->mNumFaces; j++)
				{
					if (aimesh->mFaces[j].mNumIndices == 3)
					{
						memcpy(&mesh.indices[j * 3], aimesh->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}

				// Create indices buffer
				glGenBuffers(1, (GLuint*)&(mesh.idIndices));
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.idIndices);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * mesh.numIndices, mesh.indices, GL_STATIC_DRAW);
			}

			// copy UVS ------------------------------------- 
			if (aimesh->HasTextureCoords(mesh.idUvs))
			{
				mesh.numUvs = aimesh->mNumVertices;
				mesh.uvs = new float[mesh.numUvs * 2];

				for (int i = 0; i < aimesh->mNumVertices; ++i)
				{
					memcpy(&mesh.uvs[i * 2], &aimesh->mTextureCoords[0][i].x, sizeof(float));
					memcpy(&mesh.uvs[(i * 2) + 1], &aimesh->mTextureCoords[0][i].y, sizeof(float));
				}

				// Create UVS buffer
				glGenBuffers(1, (GLuint*)&(mesh.idUvs));
				glBindBuffer(GL_ARRAY_BUFFER, mesh.idUvs);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * mesh.numUvs, mesh.uvs, GL_STATIC_DRAW);
			}

			// copy normals -------------------------------------
			if (aimesh->HasNormals())
			{
				mesh.numNormals = aimesh->mNumVertices;
				mesh.normals = new float[mesh.numNormals * 3];
				memcpy(mesh.normals, aimesh->mNormals, sizeof(float) * mesh.numNormals * 3);
				LOG("New mesh with %d normals", mesh.numNormals);

				// Create normals buffer
				glGenBuffers(1, (GLuint*)&(mesh.idNormals));
				glBindBuffer(GL_ARRAY_BUFFER, mesh.idNormals);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * mesh.numNormals, mesh.normals, GL_STATIC_DRAW);
			}

			// Get transformations --------------------------
			aiVector3D translation;
			aiVector3D scaling;
			aiQuaternion rotation;

			node->mTransformation.Decompose(scaling, rotation, translation);

			float3 position(translation.x, translation.y, translation.z);
			float3 scale(scaling.x, scaling.y, scaling.z);
			Quat _rotation(rotation.x, rotation.y, rotation.z, rotation.w);
			
			// Add ComponentTransform -->
			ComponentTransform* Ctransform = (ComponentTransform*)child->AddComponent(Transform);
			Ctransform->SetPosition(position);
			Ctransform->SetRotationQuat(_rotation);
			Ctransform->SetScale(scale);

			// Add ComponentMesh -->
			ComponentMesh* Cmesh = (ComponentMesh*)child->AddComponent(Meshes);
			Cmesh->AddMesh(mesh);

			aiMaterial* material = scene->mMaterials[aimesh->mMaterialIndex];

			if (material)
			{
				aiString path;
				material->GetTexture(aiTextureType_DIFFUSE, 0, &path);

				if (path.length > 0)
				{
					std::string basePath = "../Game/Assets/Textures/";
					std::string finalpath = path.data;
					finalpath.erase(0, finalpath.find_last_of("\\") + 1);
					basePath += finalpath;

					ComponentMaterial* c_material = (ComponentMaterial*)child->AddComponent(Material);
					c_material->textureId = LoadTexture(basePath.c_str());

					finalpath.clear();
					basePath.clear();
				}
			}
		}
	}

	for (int i = 0; i < node->mNumChildren; i++)
	{
		LoadMesh(scene, node->mChildren[i], path, child);
	}

	return child;
}

uint ModuleLoadMesh::LoadTexture(const char* path)
{
	ILuint id;
	ilGenImages(1, &id);
	ilBindImage(id);
	ilLoadImage(path);

	return ilutGLBindTexImage();
}