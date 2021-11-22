#include "Timer.h"

Timer::Timer()
{
}

// Destructor
Timer::~Timer()
{
}

unsigned int Timer::Start() 
{
	return SDL_GetTicks();
}

