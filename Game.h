#pragma once
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "SDLWindow.h"
#include "Entity.h"
#include <vector>

class GameState;

class Game
{
public:
	Game();


	void eventHandling();
	void Update();
	void Render();

	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();
	void Empty();

	void enemyTurn(std::vector<Entity*> enemies, Entity* player);
	bool Run() { return isRunning; }
	void Quit() { isRunning = false; }

	SDL_Event event;
	SDLWindow window;
private:
	std::vector<GameState*> game_states;

	bool isRunning;
};

