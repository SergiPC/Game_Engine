#ifndef __MODULE_FBX__
#define __MODULE_FBX__

#include "Module.h"
#include <vector>

struct MeshData
{
	uint id_vertices = 0; // id in VRAM 
	uint num_vertices = 0; 
	float* vertices = nullptr;

	uint id_indices = 0; // id in VRAM 
	uint num_indices = 0; 
	float* indices = nullptr;
};

class ModuleLoadFBX : public Module
{
public:
	ModuleLoadFBX(Application* app, bool start_enabled = true);
	~ModuleLoadFBX();

	bool Init();
	void Render();
	bool CleanUp();

	std::vector<MeshData> LoadFile(const char* path);

};

#endif __MODULE_FBX__