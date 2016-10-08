#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include "Component.h"
#include <vector>

class GameObject
{
public:
	GameObject(GameObject* root = nullptr);
	~GameObject();

	bool			Start();
	void			Update(float dt);
	bool			CleanUp();

	Component*		AddComponents(Type TIPE);
	void			DelComponent(Component* comp);
	Component*		FindComponent(Type TIPE);

	GameObject*		GetParent();
	void			SetParent(GameObject* parent);

	bool			IsEnable();
	void			SetEnable(bool enable);
	void			SetName(const char* new_name);
	//const char* CheckName(const char* new_name);

private:
	std::string		name;
	int				index = 1;
	GameObject*		parent;
	std::vector<GameObject*> children;
	std::vector<Component*> components;

	bool enabled;
};

#endif __GAME_OBJECT__