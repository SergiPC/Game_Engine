#ifndef __MODULE_FBX__
#define __MODULE_FBX__

#include "Globals.h"
#include "Module.h"
#include <vector>

class aiNode;
class aiScene;
class GameObject;

struct MeshData {
	uint id_vertices = 0; // id in VRAM 
	uint num_vertices = 0; 
	uint* vertices = nullptr;

	uint id_indices = 0; // id in VRAM 
	uint num_indices = 0; 
	uint* indices = nullptr;

	uint id_normals = 0;
	uint num_normals = 0;
	float* normals = nullptr;

	uint id_uvs = 0;
	uint num_uvs = 0;
	float* uvs = nullptr;
};

class ModuleLoadMesh : public Module
{
public:
	ModuleLoadMesh(Application* app, bool start_enabled = true);
	~ModuleLoadMesh();

	bool Init();
	bool CleanUp();

	std::vector<MeshData> LoadFile(const char* path);
	void LoadNode(const aiScene* scene, aiNode* child_node, GameObject* _parent, const char* _path);
	uint LoadTexture(const char* _path);
};

#endif __MODULE_FBX__