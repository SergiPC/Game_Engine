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
	void UpdateBBox(math::float4x4 world_trans);

private:
	MeshData mesh;
	math::OBB tmp_obb;
};

#endif // !__COMPONENT_MESH_H__