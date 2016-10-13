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
	int		new_height;

	// Hardware assets -----
	char sdl_compiled_info[20];

	int		cpu_number;
	int		cpu_cache;
	int		system_ram;
	bool	caps_rdtsc;
	bool	caps_mmx;
	bool	caps_sse;
	bool	caps_sse2;
	bool	caps_sse3;
	bool	caps_sse41;
	bool	caps_sse42;
	bool	caps_avx;
	bool	caps_avx2;
	bool	caps_altivec;
};

#endif // !__MENU_DIAG__
