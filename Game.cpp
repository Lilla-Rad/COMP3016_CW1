#include "Game.h"
#include "ExitState.h"
#include "LevelOneState.h"
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <stdexcept>
#include <iostream>
#include "Constants.h"
#include "SDLWindow.h"


Game::Game() {
	SDL_Event event{};
	SDL_zero(event);
	isRunning = true;
}

void Game::eventHandling() {
	game_states.back()->eventHandling(window, this);

}

void Game::Update() {
	game_states.back()->update(this, window);
}

void Game::Render() {
	game_states.back()->Render(window);
}

void Game::ChangeState(GameState* state) {
	if (!game_states.empty()) {
		game_states.back()->exit();
		game_states.pop_back();
	}
	game_states.push_back(state);
	game_states.back()->enter();
}


void Game::Empty() {
	while (!game_states.empty()) {
		game_states.back()->exit();
		game_states.pop_back();
	}
}




