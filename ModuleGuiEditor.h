#pragma once

#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"

class ModuleGuiEditor : public Module
{
public:
	ModuleGuiEditor(Application* app, bool start_enabled = true);
	~ModuleGuiEditor();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	bool CleanUp() override;

private:
};