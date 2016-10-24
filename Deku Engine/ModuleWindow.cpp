#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"

#define DEFAULT_WIDTH 1600
#define DEFAULT_HEIGHT 900

// ------------------------------------------------------------
ModuleWindow::ModuleWindow(Application* app, bool start_enabled) : Module(app, start_enabled), screen_w(DEFAULT_WIDTH), screen_h(DEFAULT_HEIGHT)
{
	window = NULL;
	screen_surface = NULL;
}

// Destructor -------------------------------------------------
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available --------------------------
bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		int width = screen_w * screen_scale;
		int height = screen_h * screen_scale;
		Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		if (fullscreen == true)
			flags |= SDL_WINDOW_FULLSCREEN;

		if (resizable == true)
			flags |= SDL_WINDOW_RESIZABLE;

		if (borderless == true)
			flags |= SDL_WINDOW_BORDERLESS;

		if (full_desktop == true)
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if (window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}
// Called before quitting -------------------------------------
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if (window != NULL)
		SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

// ------------------------------------------------------------
void ModuleWindow::SetTitle(const char* title)
{
	SDL_SetWindowTitle(window, title);
}

// ------------------------------------------------------------
void ModuleWindow::SetBorderless(bool enable)
{
	if (borderless != enable && fullscreen == false)
	{
		SDL_SetWindowBordered(window, (SDL_bool)borderless);
		borderless = enable;
	}
}

// ------------------------------------------------------------
void ModuleWindow::SetResizable(bool enable)
{
	resizable = enable;
}

// ------------------------------------------------------------
void ModuleWindow::SetFullscreen(bool enable)
{
	if (fullscreen != enable)
	{
		if (enable == true)
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		else
			SDL_SetWindowFullscreen(window, 0);

		fullscreen = enable;
	}
}

// ------------------------------------------------------------
void ModuleWindow::SetWidth(int w)
{
	screen_w = w;
	SDL_SetWindowSize(window, screen_w, screen_h);
	App->renderer3D->OnResize(screen_w, screen_h);
}

// ------------------------------------------------------------
void ModuleWindow::SetHeight(int h)
{
	screen_h = h;
	SDL_SetWindowSize(window, screen_w, screen_h);
	App->renderer3D->OnResize(screen_w, screen_h);
}

// ------------------------------------------------------------
void ModuleWindow::SetDefaultSize()
{
	screen_w = DEFAULT_WIDTH;
	screen_h = DEFAULT_HEIGHT;
	SDL_SetWindowSize(window, screen_w, screen_h);
	App->renderer3D->OnResize(screen_w, screen_h);
}

// ------------------------------------------------------------
int ModuleWindow::GetWidth()
{
	return screen_w;
}

// ------------------------------------------------------------
int ModuleWindow::GetHeight()
{
	return screen_h;
}

// ------------------------------------------------------------
int ModuleWindow::GetScale()
{
	return screen_scale;
}

// ------------------------------------------------------------
bool ModuleWindow::GetBorderlees()
{
	return borderless;
}

// ------------------------------------------------------------
bool ModuleWindow::GetResizable()
{
	return resizable;
}

// ------------------------------------------------------------
bool ModuleWindow::GetFullscreen()
{
	return fullscreen;
}