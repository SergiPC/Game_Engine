#ifndef __COMPONENT_MATERIAL_H__
#define __COMPONENT_MATERIAL_H__

#include "Component.h"

enum mat_type
{
	solid,
	alpha_test,
	blend
};

class ComponentMaterial : public Component
{
public:
	ComponentMaterial(GameObject* owner);
	~ComponentMaterial();

	bool Update();
	void OnEditor();

public:
	unsigned int name_id = 0;

private:
	mat_type kind = solid;
	float alpha_test_num = .0f;
};

#endif // !__COMPONENT_MATERIAL_H__