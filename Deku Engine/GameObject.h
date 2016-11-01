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

	bool			IsEnable() const;
	void			SetEnable(bool enable);

	bool			DeleteChild(GameObject* child);
	Component*		AddComponent(Type type);
	Component*		GetComponent(Type type);
	
	void			GenerateBBox(uint* vertices, uint num_vertices);
	void			UpdateBBox(float4x4 world_trans, float3 scale);
	const math::AABB GetBBox();
	const bool		BBoxIsEnable() const;
	void			BBoxSetEnable(bool enable);
	void			BBoxDebug();
	
public:
	GameObject*	parent = nullptr;
	std::string name;
	std::vector<GameObject*> children;
	std::vector<Component*>	components;

private:
	bool enabled = false; // GameObject enabled
	math::AABB bbox_go = math::AABB::AABB();
	math::AABB tmp_bbox_go = math::AABB::AABB();
	math::OBB tmp_obb;
	math::float4x4 world_trans_go = float4x4::zero;
	bool bbox_enabled = false;
};

#endif __GAME_OBJECT_H__
