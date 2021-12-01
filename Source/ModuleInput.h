#pragma once
#include "Module.h"
#include "Globals.h"

#include "SDL/include/SDL.h"

typedef unsigned __int8 Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status Update();
	bool CleanUp();

	inline Uint8 getKey(SDL_Scancode id);

private:
	const Uint8 *keyboard = NULL;
};

inline Uint8 ModuleInput::getKey(SDL_Scancode id)
{
	return keyboard[id];
}