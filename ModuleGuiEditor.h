#pragma once

#include "Module.h"
#include "Globals.h"

class Menu;
class MenuAbout;
class MenuHierarchy;

class ModuleGuiEditor : public Module
{
public:
	ModuleGuiEditor(Application* app, bool start_enabled = true);
	~ModuleGuiEditor();

	bool			Init();
	update_status	PreUpdate(float dt);
	update_status	Update(float dt);
	bool			CleanUp();

public:
	MenuAbout* about_menu;
	MenuHierarchy* hierarchy_menu;

private:
	std::vector<Menu*> menus_list;
	bool show_menu = true;
};