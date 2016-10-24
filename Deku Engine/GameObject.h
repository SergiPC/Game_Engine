#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#include "Globals.h"
#include <vector>

#include "MathGeoLib\src\MathGeoLib.h"

class Component;
enum componentType;

class OBB;

class GameObject
{
public:
	GameObject();
	GameObject(GameObject* parent);
	~GameObject();

	bool			Start();
	bool			Update();
	bool			CleanUp();

	bool			IsEnable();
	void			SetEnable(bool enable);

	bool			RemoveChild(GameObject* child);
	Component*		AddComponent(componentType _type);
	Component*		GetComponent(componentType _type);
	
	void			GenerateBoundingBox(uint* vertices, uint numVertices);
	
public:
	std::string		name;
	std::vector<GameObject*> children;
	std::vector<Component*>	components;

	GameObject* gameobject = this;
	GameObject* root;

	math::AABB gBox = math::AABB::AABB();

private:
	bool			enabled;
};

#endif // !__GAMEOBJECT_H__
