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
	game_states.back()->update(this);
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

void Game::PopState() {
	if (!game_states.empty()) {
		game_states.back()->exit();
		game_states.pop_back();
	}

	if (!game_states.empty()) {
		game_states.back()->enter();
	}
}

void Game::Empty() {
	while (!game_states.empty()) {
		game_states.back()->exit();
		game_states.pop_back();
	}
}

void Game::PushState(GameState* state) {
	if (!game_states.empty()) {
		game_states.back()->exit();
	}
	game_states.push_back(state);
	game_states.back()->enter();
}

bool Game::collisionCheck(SDL_Rect a, SDL_Rect b) {
	int minxA{ a.x };
	int maxxA{ a.x + a.w };
	int minyA{ a.y };
	int maxyA{ a.y + a.h };

	int minxB{ b.x };
	int maxxB{ b.x + b.w };
	int minyB{ b.y };
	int maxyB{ b.y + b.h };

	if (minxA == minxB && maxxA == maxxB && minyA == minyB && maxyA == maxyB) {
		return false;
	}

	if (minxA >= maxxB) {
		return false;
	}

	if (maxxA <= minxB) {
		return false;
	}

	if (minyA >= maxyB) {
		return false;
	}

	if (maxyA <= minyB) {
		return false;
	}

	return true;

}


/*void Entity::EntityTurn(Entity* player) {
	if (getType() == ObjectType::player) {
		std::cout << "your move";
	}
	else if (getType() == ObjectType::enemy) {
		for (int i = 0; i < getMove(); ++i) {
			int currentX = getX();
			int currentY = getY();
			int targetX = player->getX();
			int targetY = player->getY();
			std::cout << "it's MY turn hehehe";

		}
	}
}*/

void Game::enemyTurn(std::vector<Entity*> enemies, Entity* player) {
	player->setSpeed(0);
	for (int i = 0; i < enemies.size(); ++i) {
		if (enemies[i]->getType() == ObjectType::enemy && enemies[i]->getHealth() > 0) {
			for (int m = 0; m < enemies[i]->getMove(); ++m) {
				//move towards player
				//if collided with player, combat
				//std::cout << "I'M WALKIN' 'ERE\n";
				window.boxRender("enemy1 moves");
				SDL_RenderPresent(window.renderer);
				SDL_Delay(100);
			}
		}
	}
	player->setTurn(1);
	player->setMove(4);
}