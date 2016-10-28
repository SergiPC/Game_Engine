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

	bool			IsEnable();
	void			SetEnable(bool enable);

	virtual void	OnEditor();
	virtual Type	GetType() const;

public:
	GameObject* owner = nullptr;
	bool enabled;

protected:
	Type type = AMBIGUOUS;
};

#endif // !__COMPONENT_H__