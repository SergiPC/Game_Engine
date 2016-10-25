#ifndef __MENUS_H__
#define __MENUS_H__

enum MenuTypes
{
	Menu_Unknown,
	Menu_Console,
	Menu_About,
	Menu_Hierarchy,
	Menu_Inspector,
	Menu_Config
};

class Menu
{
public:
	Menu(MenuTypes type = Menu_Unknown);
	virtual ~Menu();

	void			SwitchActive();
	bool			IsActive() const;
	virtual void	Render();

	virtual void	UpdatePosSize();
	MenuTypes		GetType() const;

	void			ColorButton(int i_color);

public:
	int		width = 0;
	int		height = 0;
	int		pos_x = 0;
	int		pos_y = 0;
	bool	active = true;

protected:
	MenuTypes type;
};

#endif __MENUS_H__