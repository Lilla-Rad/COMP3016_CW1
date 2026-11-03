#pragma once
#include <SDL3/SDL.h>
#include "SDLWindow.h"
#include "Game.h"

class GameState
{
public:
	virtual bool enter() = 0;
	virtual bool exit() = 0;
	virtual void eventHandling(SDLWindow window, Game* manager) = 0;
	virtual void update(Game* manager, SDLWindow window) = 0;
	virtual void Render(SDLWindow window) = 0;

	void ChangeState(Game* manager, GameState* state) {
		manager->ChangeState(state);
	}

protected:
	GameState() {};
};

