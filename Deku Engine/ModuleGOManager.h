#ifndef __MODULE_GO_MANAGER_H__
#define __MODULE_GO_MANAGER_H__

#include "Module.h"

class GameObject;

class ModuleGOManager : public Module
{
public:
	ModuleGOManager(Application* app, bool start_enabled = true);
	~ModuleGOManager();	

	bool			Init();
	update_status	Update(float dt);
	bool			CleanUp();

	GameObject*		CreateNewGO(GameObject* parent);
	bool			DeleteGO(GameObject* go);

public:
	GameObject* root = nullptr;

private:
	uint index = 1;
	
};

#endif //!__MODULE_GO_MANAGER_H__
