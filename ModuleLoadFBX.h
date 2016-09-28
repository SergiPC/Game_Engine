#pragma once

#include "Module.h"
#include "Globals.h"
#include "p2DynArray.h"

struct MeshData
{
	uint id_vertices = 0; // id in VRAM 
	uint num_vertices = 0; 
	uint* vertices = nullptr;

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

	void LoadFile(const char* path);

private:
	p2DynArray<MeshData*> mesh_list;
};