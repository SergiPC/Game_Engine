#ifndef __MENU_HIERARCHY__
#define __MENU_HIERARCHY__

#include "Menus.h"

class MenuHierarchy : public Menu
{
public:
	MenuHierarchy();
	virtual ~MenuHierarchy();

	void Render();
	void RenderChildren(GameObject* _parent);
	void UpdatePosSize();

public:
	const char* name[50];
	GameObject* h_root = nullptr;
	GameObject* tmp_go = nullptr;
};

#endif __MENU_HIERARCHY__