#ifndef  __MODULELOADMESHES_H__
#define __MODULELOADMESHES_H__

#include "Module.h"
#include "MathGeoLib\src\MathGeoLib.h"

#include <cstdint>
#include <vector>

class aiNode;
class aiScene;
class GameObject;

struct MeshData
{
	uint id_vertices = 0;
	uint num_vertices = 0;
	uint* vertices = nullptr;

	uint id_indices = 0;
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

	std::vector<GameObject*> LoadFile(const char* path);
	GameObject* LoadMesh(const aiScene* scene, aiNode* node, GameObject* parent, const char* path);
	uint LoadTexture(const char* path);
};

#endif // __MODULEMESHES_H__
