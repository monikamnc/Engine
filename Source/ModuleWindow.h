#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();

	// Destructor
	virtual ~ModuleWindow();

	// Called on start
	bool Init();

	// Called before quitting
	bool CleanUp();

	inline void setScreenSize(unsigned newWidth, unsigned newHeight);

public:
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screen_surface = NULL;


	bool show_another_window = true;

private:
	unsigned screenWidth;
	unsigned screenHeight;

};

inline void ModuleWindow::setScreenSize(unsigned newWidth, unsigned newHeight)
{
	screenWidth = newWidth;
	screenHeight = newHeight;
}
#endif // __ModuleWindow_H__