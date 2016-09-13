#pragma once

#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"

class Editor : public Module
{
public:
	Editor(Application* app, bool start_enabled = true);
	~Editor();

	bool Init() override;
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	bool CleanUp() override;
	
	void HandleInput(SDL_Event* event);

	void Draw();
	bool IsHovered();

private:
};