#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include "Component.h"
#include "ModuleGOManager.h"
#include <vector>

class GameObject
{
public:
	GameObject(GameObject* root = nullptr);
	~GameObject();

	bool Start();
	void Update(float dt);
	bool CleanUp();

	Component* AddComponents(Component* type);
	void DelComponent(Component* comp);
	Component* FindComponent(Type type);
	std::vector<Component*> FindComponentsVec(Type type);

	GameObject* GetParent();
	void SetParent(GameObject* parent);
	void SetName(const char* new_name);
	const char* CheckName(const char* new_name);

	bool IsEnable();
	void SetEnable(bool enable);

private:
	std::string name;
	int index = 1;
	GameObject* parent;
	std::vector<GameObject*> children;
	std::vector<Component*> components;

	bool enabled;
};

#endif __GAME_OBJECT__