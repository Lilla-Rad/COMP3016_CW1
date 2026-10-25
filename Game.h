#pragma once
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "GameState.h"
#include "StateManager.h"
#include "SDLWindow.h"

class Game
{
public:
	Game();
	void Run();
	StateManager manager;
	GameState* initState;
	SDL_Event event;
	SDLWindow window;
};

