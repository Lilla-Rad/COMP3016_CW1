#pragma once
#include <SDL3/SDL.h>
#include "SDLWindow.h"

class GameState
{
public:
	virtual bool enter() = 0;
	virtual bool exit() = 0;
	virtual void eventHandling(SDL_Event& e, SDLWindow window) = 0;
	virtual void update() = 0;
	virtual void Render(SDLWindow window) = 0;

	virtual	~GameState() {};
};

