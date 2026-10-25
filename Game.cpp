#include "Game.h"
#include "StateManager.h"
#include "ExitState.h"
#include "LevelOneState.h"
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <stdexcept>
#include <iostream>
#include "Constants.h"
#include "SDLWindow.h"

Game::Game() {
	SDL_Event event;
	SDL_zero(event);
	StateManager manager;
	/*try {
		window.Init();
	}
	catch (const std::runtime_error& e) {
		std::cout << e.what() << std::endl;
		window.Quit();
	}*/

}



void Game::Run() {
	manager.currentState = LevelOneState::get();
	manager.currentState->enter();
	bool run = true;
	while (manager.currentState != ExitState::get()) {
		while (SDL_PollEvent(&event) != 0) {
			manager.currentState->eventHandling(event, window);
			if (event.type == SDL_EVENT_QUIT || event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
				manager.setNextState(ExitState::get());
			}
		}
		manager.currentState->update();
		manager.changeState();
		manager.currentState->Render(window);
	}
}

