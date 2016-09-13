#pragma once

#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"

class Editor : public Module
{
public:
	Editor(Application* app, bool start_enabled = true);
	~Editor();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	bool CleanUp() override;

private:
};