#ifndef __COMPONENT__
#define __COMPONENT__

//#include "glmath.h"
#include "MathGeoLib/MathBuildConfig.h"
#include "MathGeoLib/MathGeoLib.h"

class GameObject;

enum Type
{
	TRANSFORM,
	MATERIAL,
	MESH
};

class Component
{
public:
	Component(GameObject* _parent, Type TIPE);

	virtual void	Update();
	virtual void	OnEditor();
	bool			IsEnable();
	void			SetEnable(bool enable);
	Type			GetType();
	GameObject*		GetParent();
	bool			CleanUp();

private:
	bool		enabled;
	GameObject*	parent;

protected:
	Type	type;
};

#endif __COMPONENT__