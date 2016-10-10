#ifndef __MENU_HIERARCHY__
#define __MENU_HIERARCHY__

#include "Menus.h"

class MenuHierarchy : public Menu
{
public:
	MenuHierarchy();
	virtual ~MenuHierarchy();

	void Render();

public:
	const char* name[50];
};

#endif __MENU_HIERARCHY__