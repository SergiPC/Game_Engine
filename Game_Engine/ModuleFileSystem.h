#ifndef __MODULE_FILE_SYSTEM__
#define __MODULE_FILE_SYSTEM__

#include "Module.h"

struct SDL_RWops;
int close_sdl_rwops(SDL_RWops *rw);

class ModuleFileSystem : public Module
{
public:
	ModuleFileSystem(Application* app, bool start_enabled = true, const char* game_path = nullptr);
	~ModuleFileSystem();

	// Called before render is available
	bool Init();

	// Utility functions
	bool AddPath(const char* path_or_zip, const char* mount_point = nullptr);
	bool Exists(const char* file) const;
	bool IsDirectory(const char* file) const;
	const char* GetSaveDirectory() const
	{
		return "save/";
	}

	//Sets a Write Directory
	bool SetWriteDirectory();
	bool SaveFileExists();
	bool DeleteSaveFile();

	// Open for Read/Write
	unsigned int Load(const char* file, char** buffer) const;
	SDL_RWops* Load(const char* file) const;
	unsigned int Save(const char* file, const char* buffer, unsigned int size) const;

	// Called before quitting
	bool CleanUp();
};

#endif //__MODULE_FILE_SYSTEM__