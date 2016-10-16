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
	void			SetName(const char* new_name);

	// Add a standard component
	Component*		AddComponent(Type TIPE);
	void			DelComponent(Component* comp);
	Component*		GetComponent(Type TIPE);

	// Add especific component
	//ComponentTransform*	AddTransform();
	//ComponentMesh*		AddMesh(MeshData _mesh);
	//ComponentMaterial*	AddMaterial(size_t _name_id);

	void			Translate(float3 new_pos);
	void			Rotate(float3 new_euler);
	void			Rotate(Quat new_quat);
	void			Scale(float3 new_scale);

	GameObject*		GetParent();
	void			SetParent(GameObject* parent);

public:
	std::string		name;
	std::vector<GameObject*> children;
	std::vector<Component*> components;

private:
	GameObject*		parent;
	bool			enabled;

	float3			position;
	float3			euler_rotation;
	Quat			quat_rotation;
	float3			scale;
	float4x4		tranform;
};

#endif __GAME_OBJECT__