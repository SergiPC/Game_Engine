#ifndef __MODULE_GO_MANAGER__
#define __MODULE_GO_MANAGER__

#include "Module.h"

class GameObject;

class ModuleGOManager : public Module
{
public:
	ModuleGOManager(Application* app, bool start_enabled = true);
	~ModuleGOManager();

	bool			Start();
	update_status	Update(float dt);
	bool			CleanUp();

	GameObject*		CreateNewGO(GameObject* parent = nullptr);
	void			DeleteGO(GameObject* go);
	GameObject*		GetRoot();

private:
	GameObject* root = nullptr;

	std::string name;
	int index = 1;
};

#endif __MODULE_GO_MANAGER__