#ifndef __MENU_CONFIG_H__
#define __MENU_CONFIG_H__

#include "Menus.h"
#include <vector>

class MenuConfig : public Menu
{
public:
	MenuConfig();
	virtual ~MenuConfig();

	void	Render();
	void	UpdatePosSize();
	void	CalculateParameters(float current_fps, float current_ms);

private:
	std::vector<float> fps;
	std::vector<float> ms;
	int	bar_num = 0;

	// Window assets -----
	bool	fullscreen = false;
	bool	resizable = false;
	bool	borderless = false;
	bool	full_desktop = false;
	int		new_width = 0;
	int		new_height = 0;

	// Hardware assets -----
	char sdl_compiled_info[20];

	int		cpu_number = 0;
	int		cpu_cache = 0;
	int		system_ram = 0;
	bool	caps_rdtsc = false;
	bool	caps_mmx = false;
	bool	caps_sse = false;
	bool	caps_sse2 = false;
	bool	caps_sse3 = false;
	bool	caps_sse41 = false;
	bool	caps_sse42 = false;
	bool	caps_avx = false;
	bool	caps_avx2 = false;
	bool	caps_altivec = false;
};

#endif // !__MENU_CONFIG_H__
