#ifndef __COMPONENT_H__
#define __COMPONENT_H__

class GameObject;

enum Type
{
	AMBIGUOUS,
	TRANSFORM,
	MATERIAL,
	MESH
};

class Component
{
public:
	Component(GameObject* owner, Type type);
	~Component();

	virtual bool	Init();
	virtual bool	Update();

	const bool		IsEnable() const;
	void			SetEnable(bool enable);
	virtual void	OnEditor();

	const Type			GetType() const;
	const GameObject*	GetGO() const;

protected:
	GameObject* owner = nullptr;
	Type type = AMBIGUOUS;
	bool enabled = false;
};

#endif // !__COMPONENT_H__