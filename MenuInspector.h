#ifndef __MENU_INSPECTOR__
#define __MENU_INSPECTOR__

#include "Menus.h"

class MenuInspector : public Menu
{
public:
	MenuInspector();
	virtual ~MenuInspector();

	void Render();
};

#endif // !__MENU_INSPECTOR__
