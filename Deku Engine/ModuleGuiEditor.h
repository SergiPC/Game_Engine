#ifndef __MODULE_GUI__
#define __MODULE_GUI__

#include "Module.h"
#include "Globals.h"

class Menu;
class MenuAbout;
class MenuHierarchy;
class MenuInspector;
class MenuConfig;
class GameObject;

class ModuleGuiEditor : public Module
{
public:
	ModuleGuiEditor(Application* app, bool start_enabled = true);
	~ModuleGuiEditor();

	bool			Init();
	update_status	PreUpdate(float dt);
	update_status	Update(float dt);
	void			UpdatePosSize();
	void			CalcPar(float current_fps, float current_ms);
	bool			CleanUp();

public:
	MenuAbout*		about_menu;
	MenuHierarchy*	hierarchy_menu;
	MenuInspector*	inspector_menu;
	MenuConfig*		diagnostic_menu;
	GameObject*		selected_go = nullptr;

private:
	std::vector<Menu*> menus_list;
	bool show_menu = true;
};
#endif // !__MODULE_GUI__
