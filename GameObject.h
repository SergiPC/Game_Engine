#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"
#include <vector>
struct MeshData;


class GameObject
{
public:
	GameObject(GameObject* _parent, const char* _name);
	~GameObject();

	bool			Start();
	void			Update();
	bool			CleanUp();

	bool			IsEnable();
	void			SetEnable(bool enable);

	Component*		AddComponent(Type TIPE);
	Component*		GetComponent(Type TIPE);
	void			DelComponent(Component* comp);
	void			DelChild(GameObject* go_child);

	GameObject*		GetParent();
	void			SetParent(GameObject* parent);

public:
	std::string		name;
	std::vector<GameObject*> children;
	std::vector<Component*> components;

private:
	GameObject*		parent;
	bool			enabled;
};

#endif __GAME_OBJECT__