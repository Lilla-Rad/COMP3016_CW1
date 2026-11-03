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




/*void Game::cutscene(Entity* player) {
	SDL_Delay(50);
	player->MoveDown();
	player->dialogue(window, "Phew... I think I lost them...", 1, 50);
}*/




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




/*void Game::enemyTurn(std::vector<Entity*> enemies, Entity* player) {
	window.boxRender("ENEMY TURN");
	SDL_RenderPresent(window.renderer);
	SDL_Delay(500);
	player->setSpeed(0);
	for (int i = 1; i < enemies.size()-1; ++i) {
		if (enemies[i]->getType() == ObjectType::enemy && enemies[i]->getHealth() > 0) {
			/*std::cout << enemies[i]->getBounds().x;
			std::cout << "\n";
			std::cout << enemies[i]->getBounds().y;
			std::cout << "\n";
			std::cout << enemies[i]->getBounds().w;
			std::cout << "\n";
			std::cout << enemies[i]->getBounds().h;
			std::cout << "\n";
			for (int m = 0; m < enemies[i]->getMove(); ++m) {
				//move towards player
				//if collided with player, combat
				window.boxRender("Enemy " + std::to_string(i) + " moves");

				int currentX = enemies[i]->getX();
				int currentY = enemies[i]->getY();
				int targetX = player->getX();
				int targetY = player->getY();
				//if enemy is to player's right
				if (targetX < currentX) {
					enemies[i]->MoveLeft();
				}
				//if enemy is to player's left
				if (targetX > currentX){
					enemies[i]->MoveRight();
				}
				//if enemy is above player
				if (targetY > currentY) {
					enemies[i]->MoveDown();
				}
				//if enemy is below player
				if (targetY < currentY) {
					enemies[i]->MoveUp(/*enemies, i);
					
				}
				SDL_RenderPresent(window.renderer);
				SDL_Delay(500);

			}
		}
	}
	player->setTurn(1);
	//player->setMove(4);
	for (int i = 0; i < enemies.size(); ++i) {
		enemies[i]->setMove(4);
	}
	window.boxRender("PLAYER TURN");
	SDL_RenderPresent(window.renderer);
	SDL_Delay(500);
}*/

