#include "Application.h"
#include "ModuleLoadFBX.h"

#include "Assimp/include/cimport.h" 
#include "Assimp/include/scene.h" 
#include "Assimp/include/postprocess.h" 
#include "Assimp/include/cfileio.h"

#include "Glew\include\glew.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")
#pragma comment (lib, "Glew/libx86/glew32.lib")

using namespace std;

ModuleLoadFBX::ModuleLoadFBX(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

// Destructor
ModuleLoadFBX::~ModuleLoadFBX()
{}

// Called before render is available
bool ModuleLoadFBX::Init()
{
	// Stream log messages to Debug window 
	//struct aiLogStream stream; 
	//stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr); 
	//aiAttachLogStream(&stream);

	bool ret = true;

	return ret;
}

void ModuleLoadFBX::Render()
{}

vector<MeshData> ModuleLoadFBX::LoadFile(const char* path)
{
	vector<MeshData> all_mesh;
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* new_mesh = scene->mMeshes[i];
			MeshData m;

			// copy vertices 
			m.num_vertices = new_mesh->mNumVertices;
			m.vertices = new float[m.num_vertices * 3];
			memcpy(m.vertices, new_mesh->mVertices, sizeof(float) * m.num_vertices * 3);
			LOG("New mesh with %d vertices", m.num_vertices);

			// Create vertice buffer
			glGenBuffers(1, (GLuint*) &(m.id_vertices));
			glBindBuffer(GL_ARRAY_BUFFER, m.id_vertices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * m.num_vertices, m.vertices, GL_STATIC_DRAW);

			// copy faces 
			if (new_mesh->HasFaces()) 
			{  
				m.num_indices = new_mesh->mNumFaces * 3; 
				m.indices = new float[m.num_indices]; // assume each face is a triangle  
				
				for (uint j = 0; j < new_mesh->mNumFaces; ++j)  
				{   
					if (new_mesh->mFaces[j].mNumIndices != 3)
					{
						LOG("WARNING, geometry face with != 3 indices!");
					}

					else
						memcpy(&m.indices[j * 3], new_mesh->mFaces[j].mIndices, 3 * sizeof(uint));
				} 
			}

			// Create indices buffer
			glGenBuffers(1, (GLuint*) &(m.id_indices));
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.id_indices);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * m.num_indices, m.indices, GL_STATIC_DRAW);

			all_mesh.push_back(m);
		}

		aiReleaseImport(scene);
	}

	else
		LOG("Error loading scene %s", path);

	return all_mesh;
}

bool ModuleLoadFBX::CleanUp()
{
	// detach log stream 
	aiDetachAllLogStreams();
	
	bool ret = true;

	return ret;
}
