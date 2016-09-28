#include "Globals.h"
#include "Application.h"
#include "ModuleLoadFBX.h"
#include "Assimp/include/cimport.h" 
#include "Assimp/include/scene.h" 
#include "Assimp/include/postprocess.h" 
#include "Assimp/include/cfileio.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

ModuleLoadFBX::ModuleLoadFBX(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

// Destructor
ModuleLoadFBX::~ModuleLoadFBX()
{}

// Called before render is available
bool ModuleLoadFBX::Init()
{
	// Stream log messages to Debug window 
	struct aiLogStream stream; 
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr); 
	aiAttachLogStream(&stream);

	bool ret = true;

	return ret;
}

void ModuleLoadFBX::Render()
{}

void ModuleLoadFBX::LoadFile(const char* path)
{
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array   
		aiReleaseImport(scene);
	}

	else
		LOG("Error loading scene %s", path);
}

bool ModuleLoadFBX::CleanUp()
{
	// detach log stream 
	aiDetachAllLogStreams();
	
	bool ret = true;

	return ret;
}
