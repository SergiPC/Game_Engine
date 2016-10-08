#ifndef __COMPONENT__
#define __COMPONENT__

enum Type
{
	TRANFORM,
	AUDIO,
	CAMERA,
	MATERIAL,
	MESH
};

class Component
{
public:
	Component()
	{}

	virtual ~Component()
	{}

	// -----------------------------------------------------------------
	virtual bool Start()
	{
		return true;
	}

	// -----------------------------------------------------------------
	virtual update_status Update(float dt)
	{
		return UPDATE_CONTINUE;
	}

	// -----------------------------------------------------------------
	virtual bool Enable()
	{
		if (enabled == false)
		{
			enabled = true;
			Start();
		}
	}

	// -----------------------------------------------------------------
	virtual void Desable()
	{
		if (enabled == true)
		{
			enabled = false;
			CleanUp();
		}
	}

	// -----------------------------------------------------------------
	virtual Type GetType()
	{
		return type;
	}

	// -----------------------------------------------------------------
	virtual bool CleanUp()
	{
		return true;
	}

private:
	bool enabled;
	Type type;

};

#endif __COMPONENT__