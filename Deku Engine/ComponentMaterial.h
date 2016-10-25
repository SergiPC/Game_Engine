#ifndef __COMPONENT_MATERIAL_H__
#define __COMPONENT_MATERIAL_H__

#include "Component.h"

class ComponentMaterial : public Component
{
public:
	ComponentMaterial(GameObject* owner);
	~ComponentMaterial();

	bool Update();
	void OnEditor();

public:
	unsigned int name_id = 0;
};

#endif // !__COMPONENT_MATERIAL_H__