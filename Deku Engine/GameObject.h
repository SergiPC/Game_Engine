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
	
	math::AABB		GetBBox();
	void			GenerateBBox(uint* vertices, uint num_vertices);
	void			UpdateBBox(float4x4 world_trans);
	
public:
	GameObject*	parent = nullptr;
	std::string name;
	std::vector<GameObject*> children;
	std::vector<Component*>	components;

private:
	bool enabled = false;
	math::AABB bbox_go = math::AABB::AABB();
	math::OBB tmp_obb;
};

#endif __GAME_OBJECT_H__
