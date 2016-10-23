#ifndef __COMPONENT_MATERIAL__
#define __COMPONENT_MATERIAL__

#include "Component.h"

class ComponentMaterial : public Component
{
public:
	ComponentMaterial(GameObject* _parent);
	~ComponentMaterial();

	void Update();
	void OnEditor();
	unsigned int GetId();

public:
	unsigned int name_id;

};
#endif // !__COMPONENT_MATERIAL__
