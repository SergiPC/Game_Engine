#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "Globals.h"
#include "Component.h"
#include <vector>

#include "MathGeoLib\src\MathGeoLib.h"

class OBB;

class GameObject
{
public:
	GameObject(GameObject* parent);
	~GameObject();

	bool			Start();
	bool			Update();
	bool			CleanUp();

	bool			IsEnable();
	void			SetEnable(bool enable);

	bool			DeleteChild(GameObject* child);
	Component*		AddComponent(Type type);
	Component*		GetComponent(Type type);
	void			DeleteComponent(Component* comp);
	
	void			GenerateBoundingBox(uint* vertices, uint numVertices);
	
public:
	GameObject*	parent = nullptr;
	std::string name;
	std::vector<GameObject*> children;
	std::vector<Component*>	components;

private:
	bool enabled = false;
	math::AABB gBox = math::AABB::AABB();
};

#endif __GAME_OBJECT_H__
