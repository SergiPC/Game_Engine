#ifndef __MODULE_WINDOW_H__
#define __MODULE_WINDOW_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init();
	bool CleanUp();

	void	SetTitle(const char* title);
	void	SetBorderless(bool enable);
	void	SetResizable(bool enable);
	void	SetFullscreen(bool enable);
	void	SetWidth(int w);
	void	SetHeight(int h);
	void	SetDefaultSize();
	// Maybe I can implement a method to change size of "menus"

	int		GetWidth();
	int		GetHeight();
	int		GetScale();
	bool	GetBorderlees();
	bool	GetResizable();
	bool	GetFullscreen();

public:
	// The window we'll be rendering to
	SDL_Window* window;

	// The surface contained by the window
	SDL_Surface* screen_surface;

private:
	int		screen_w;
	int		screen_h;
	int		screen_scale = 1;
	bool	fullscreen = false;
	bool	resizable = true;
	bool	borderless = false;
	bool	full_desktop = false;
};

#endif // __MODULE_WINDOW_H__