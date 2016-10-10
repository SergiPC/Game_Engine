#ifndef __MENU_DIAG__
#define __MENU_DIAG__

#include "Menus.h"
#include <vector>

class MenuDiagnostic : public Menu
{
public:
	MenuDiagnostic();
	virtual ~MenuDiagnostic();

	void Render();
	void CalculateFPS(float current_fps);

private:
	std::vector<float> fps;
	int bar_num = 0;
};

#endif // !__MENU_DIAG__
