#ifndef __MENU_ABOUT_H__
#define __MENU_ABOUT_H__

#include "Menus.h"

class MenuAbout : public Menu
{
public:
	MenuAbout();
	virtual ~MenuAbout();

	void Render();
};

#endif __MENU_ABOUT_H__
