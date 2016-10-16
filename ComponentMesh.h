#ifndef __COMPONENT_MESH__
#define __COMPONENT_MESH__

#include "Component.h"
#include "ModuleLoadMesh.h"

struct MeshData;

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* _parent);
	~ComponentMesh();

	void Update();
	void SetMesh(MeshData new_mesh);
	//void OnEditor();

private:
	MeshData mesh;
};

#endif // !__COMPONENT_MESH__

