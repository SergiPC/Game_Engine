#pragma once
#include "Globals.h"
#include "SDL/include/SDL_scancode.h"

enum MenuTypes
{
	Menu_Unknown,
	Menu_Console,
	Menu_About
};

class Menu
{
public:
	Menu(MenuTypes type = Menu_Unknown);
	virtual ~Menu();

	void SwitchActive();
	bool GetActive() const;
	virtual void Render();
	MenuTypes GetType() const;	

public:
	int width, height, pos_x, pos_y;
	bool active = true;

protected:
	MenuTypes type;
};