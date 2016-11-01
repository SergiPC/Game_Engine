#ifndef __COMPONENT_MESH_H__
#define __COMPONENT_MESH_H__

#include "Component.h"
#include "ModuleLoadMesh.h"

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* owner);
	~ComponentMesh();
	
	bool Update();
	void OnEditor();

	void SetMesh(MeshData new_mesh);

private:
	MeshData mesh;
};

#endif // !__COMPONENT_MESH_H__