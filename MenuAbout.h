#pragma once
#include "Menus.h"

class MenuAbout : public Menu
{
public:
	MenuAbout();
	virtual ~MenuAbout();

	void Render();
};