#ifndef __MODULE_GO_MANAGER__
#define __MODULE_GO_MANAGER__

#include "Module.h"
#include "GameObject.h"

class ModuleGOManager : public Module
{
public:
	ModuleGOManager(Application* app, bool start_enabled = true);
	~ModuleGOManager();

	bool			Start();
	update_status	Update(float dt);
	bool			CleanUp();

	GameObject*		CreateNewGO(GameObject* parent);
	void			DeleteGO(GameObject* go);
	GameObject*		DuplicateGO(GameObject* go);
	void			SetParent(GameObject* go, GameObject* parent);

	std::vector<GameObject*> GetGOVector();

public:
	std::vector<GameObject*> game_objects_list;

private:
	GameObject* root;
};

#endif __MODULE_GO_MANAGER__