#include "Globals.h"
#include "Application.h"
#include "ModuleLoadMesh.h"
#include "GameObject.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "Assimp.h"

#include "Glew\include\glew.h"
#include "Devil.h"

using namespace std;

// -----------------------------------------------------------------
ModuleLoadMesh::ModuleLoadMesh(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

// -----------------------------------------------------------------
ModuleLoadMesh::~ModuleLoadMesh()
{}

// -----------------------------------------------------------------
bool ModuleLoadMesh::Init()
{
	// Stream log messages to Debug window 
	//struct aiLogStream stream; 
	//stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr); 
	//aiAttachLogStream(&stream);

	// Devil
	ilInit();
	iluInit();
	ilutInit();

	// Before you call any ilut functions
	ilutRenderer(ILUT_OPENGL);

	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
vector<MeshData> ModuleLoadMesh::LoadFile(const char* path)
{
	vector<MeshData> all_mesh;
	
	// Start from aiScene::mRootNode then go recursive from there.
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		aiNode* parent_node = scene->mRootNode;

		GameObject* parent_go = App->go_manager->CreateNewGO();
		const char* tmp_str = parent_node->mName.data;
		parent_go->SetName(tmp_str);

		// Then loop aiNode::mNumChildren
		for (int j = 0; j < parent_node->mNumChildren; j++)
		{
			// ... then deal with each aiNode::mChildren[n]
			LoadNode(scene, parent_node->mChildren[j], parent_go, path);
		}

		aiReleaseImport(scene);
	}

	else
		LOG("Error loading scene %s", path);

	return all_mesh;
}

// -----------------------------------------------------------------
void ModuleLoadMesh::LoadNode(const aiScene* scene, aiNode* child_node, GameObject* _parent, const char* _path)
{
	GameObject* child_go = App->go_manager->CreateNewGO(_parent);
	const char* tmp2_str = child_node->mName.data;
	child_go->SetName(tmp2_str);

	if (child_node->mNumMeshes > 0)
	{
		for (int i = 0; i < child_node->mNumMeshes; i++)
		{
			aiMesh* new_mesh = scene->mMeshes[child_node->mMeshes[i]];
			MeshData m = MeshData();

			// copy vertices ------------------------------------
			m.num_vertices = new_mesh->mNumVertices;
			m.vertices = new uint[m.num_vertices * 3];
			memcpy(m.vertices, new_mesh->mVertices, sizeof(float) * m.num_vertices * 3);
			LOG("New mesh with %d vertices", m.num_vertices);

			// Create vertice buffer
			glGenBuffers(1, (GLuint*) &(m.id_vertices));
			glBindBuffer(GL_ARRAY_BUFFER, m.id_vertices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * m.num_vertices, m.vertices, GL_STATIC_DRAW);

			// copy indices -------------------------------------
			// copy faces 
			if (new_mesh->HasFaces())
			{
				m.num_indices = new_mesh->mNumFaces * 3;
				m.indices = new uint[m.num_indices]; // assume each face is a triangle  

				for (uint k = 0; k < new_mesh->mNumFaces; ++k)
				{
					if (new_mesh->mFaces[k].mNumIndices != 3)
					{
						LOG("WARNING, geometry face with != 3 indices!");
					}

					else
						memcpy(&m.indices[k * 3], new_mesh->mFaces[k].mIndices, 3 * sizeof(uint));
				}

				// Create indices buffer
				glGenBuffers(1, (GLuint*) &(m.id_indices));
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.id_indices);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * m.num_indices, m.indices, GL_STATIC_DRAW);
			}

			// copy normals -------------------------------------
			if (new_mesh->HasNormals())
			{
				m.num_normals = new_mesh->mNumVertices;
				m.normals = new float[m.num_normals * 3];
				memcpy(m.normals, new_mesh->mVertices, sizeof(float) * m.num_normals * 3);
				LOG("New mesh with %d normals", m.num_normals);

				// Create normals buffer
				glGenBuffers(1, (GLuint*) &(m.id_normals));
				glBindBuffer(GL_ARRAY_BUFFER, m.id_normals);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * m.num_normals, m.normals, GL_STATIC_DRAW);
			}

			// copy UVS ------------------------------------- 
			if (new_mesh->HasTextureCoords(m.id_uvs))
			{
				m.num_uvs = new_mesh->mNumVertices;
				m.uvs = new float[m.num_uvs * 2];

				for (uint l = 0; l < new_mesh->mNumVertices; ++l)
				{
					memcpy(&m.uvs[l * 2], &new_mesh->mTextureCoords[0][l].x, sizeof(float));
					memcpy(&m.uvs[(l * 2) + 1], &new_mesh->mTextureCoords[0][l].y, sizeof(float));
				}

				// Create UVS buffer
				glGenBuffers(1, (GLuint*) &(m.id_uvs));
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.id_uvs);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 2 * m.num_uvs, m.uvs, GL_STATIC_DRAW);
			}

			// Get transformations --------------------------
			aiVector3D pos;
			aiVector3D sca;
			aiQuaternion quat;
			aiVector3D e_rot = child_node->mTransformation.GetEuler();

			child_node->mTransformation.Decompose(sca, quat, pos);

			// Add ComponentTransform -->
			ComponentTransform* trans_comp = (ComponentTransform*)child_go->AddComponent(TRANSFORM);
			trans_comp->SetPos(pos.x, pos.y, pos.z);
			trans_comp->SetScale(sca.x, sca.y, sca.y);
			trans_comp->SetRotation(e_rot.x, e_rot.y, e_rot.z);

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
						std::string texture_path = "Library/Textures/";
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

	else
	{
		// Get transformations --------------------------
		aiVector3D pos;
		aiVector3D sca;
		aiQuaternion quat;
		aiVector3D e_rot = child_node->mTransformation.GetEuler();

		child_node->mTransformation.Decompose(sca, quat, pos);

		// Add ComponentTransform -->
		ComponentTransform* trans_comp = (ComponentTransform*)child_go->AddComponent(TRANSFORM);
		trans_comp->SetPos(pos.x, pos.y, pos.z);
		trans_comp->SetScale(sca.x, sca.y, sca.y);
		trans_comp->SetRotation(e_rot.x, e_rot.y, e_rot.z);
	}

	for (int n = 0; n < child_node->mNumChildren; n++)
	{
		LoadNode(scene, child_node->mChildren[n], child_go, _path);
	}
}

// -----------------------------------------------------------------
uint ModuleLoadMesh::LoadTexture(const char* _path)
{
	ILuint ImageName;

	// generate an image name
	ilGenImages(1, &ImageName);

	// bind image name
	ilBindImage(ImageName);

	ilLoadImage(_path);

	return ilutGLBindTexImage();
}

// -----------------------------------------------------------------
bool ModuleLoadMesh::CleanUp()
{
	// detach log stream 
	//aiDetachAllLogStreams();
	
	//ilDeleteImages(1, &ImageName);

	bool ret = true;

	return ret;
}
