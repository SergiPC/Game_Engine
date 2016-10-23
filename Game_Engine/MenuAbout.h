#ifndef __MENU_ABOUT__
#define __MENU_ABOUT__

#include "Menus.h"

class MenuAbout : public Menu
{
public:
	MenuAbout();
	virtual ~MenuAbout();

	void Render();
};

#endif __MENU_ABOUT__