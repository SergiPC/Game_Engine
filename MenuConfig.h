#ifndef __MENU_DIAG__
#define __MENU_DIAG__

#include "Menus.h"
#include <vector>

class MenuConfig : public Menu
{
public:
	MenuConfig();
	virtual ~MenuConfig();

	void Render();
	void CalculateParameters(float current_fps, float current_ms);

private:
	std::vector<float> fps;
	std::vector<float> ms;
	int	bar_num = 0;

	// Window assets -----
	bool	fullscreen;
	bool	resizable;
	bool	borderless;
	bool	full_desktop;

	int		new_width;
};

#endif // !__MENU_DIAG__
