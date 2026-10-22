#include "Game.h"
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "Entity.h"
#include <iostream>
#include "Constants.h"
#include "Tile.h"
#include "escapeTile.h"
#include <SDL3_image/SDL_image.h>
#include <vector>

bool Game::init() {
	bool success{ true };

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == false) {
		SDL_Log("SDL failed to initialise! SDL error: %s\n", SDL_GetError());
		success = false;
	}

	if (SDL_CreateWindowAndRenderer("test", WINDOW_WIDTH, WINDOW_HEIGHT, NULL, &window, &renderer) == false) {
		SDL_Log("Could not create window! SDL error: %s\n", SDL_GetError());
	}
	else {
		if (MIX_Init() == false) {
			SDL_Log("Could not initialise mixer! SDL_mixer error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			if (mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr); mixer == nullptr) {
				SDL_Log("SDL_mixer failed to create mixer! SDL_mixer error: %s\n", SDL_GetError());
				success = false;
			}
		}
	}
	return success;
}

Game::Game() {
	init();
	/*window = SDL_CreateWindow("test", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_EVENT_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, NULL);*/
	mixer = nullptr;
	texture = nullptr;
	MIX_Audio* kissy{ nullptr };
	MIX_Track* kissiing{ nullptr };
	level = 1;
	//map = new LoadTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	player = new Entity(0, WINDOW_HEIGHT / 2 - PLAYER_HEIGHT / 2, 5, 1, 1, 20, 10, 10, 9999999999, "WhatsApp Image 2026-10-13 at 16.58.09.jpeg", { 0, 0, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::player);
	
	escape = new escapeTile(50, WINDOW_HEIGHT / 3 - PLAYER_HEIGHT / 3, 0, 0, 20, "theyretryingokay.png", { WINDOW_WIDTH - 5, WINDOW_HEIGHT - 5, PLAYER_WIDTH, PLAYER_HEIGHT}, ObjectType::escape);
	enemy1 = new Entity(WINDOW_WIDTH - PLAYER_WIDTH - 20, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2, 5, 0, 0, 20, 20, 20, 4, "pinagaling.png", { WINDOW_WIDTH - PADDLE_WIDTH - 20, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::enemy);
	temp = new Temp(WINDOW_WIDTH / 2 - BALL_SIZE / 2, WINDOW_HEIGHT / 2 - BALL_SIZE / 2, BALL_SPEED, BALL_SPEED);
	//array of collidable objects in level. [0] is always player, [1] is always the escape tile
	//Object* collidables[3] = { player, escape, enemy1 };
	collidables = { player, escape, enemy1 };

}

void Game::levelSetup(int level) {
	if (level == 2) {
		player->setX(5);
		SDL_Delay(50);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		renderTextureFromFile("WhatsApp Image 2026-10-13 at 16.58.09.jpeg", NULL, NULL);
		SDL_RenderPresent(renderer);
		SDL_Delay(5000);
	}
}



Game::~Game() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
};

void Game::gameOver() {
	SDL_Delay(50);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	renderTextureFromFile("WhatsApp Image 2026-10-13 at 16.58.09.jpeg", NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_Delay(5000);
}

void Game::gameWin() {
	if (level < 3) {
		level += 1;
		levelSetup(level);
	}
	else {
	}
}

void Game::Run() {
	while (true) {
		if (player->getHealth() <= 0) {
			gameOver();
			SDL_RenderClear(renderer);
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			exit(0);
		}
		else {
			//playerturn
			//currentState->
			Input();
			//enemyturn
			temp->update(player->getX(), player->getY(), enemy1->getX(), enemy1->getY());
			SDL_Delay(30);
			/*std::cout << "Player:";
			std::cout << player->getX();
			std::cout << " ";
			std::cout << player->getY();
			std::cout << " ";
			std::cout << "Enemy:";
			std::cout << enemy1->getX();
			std::cout << " ";
			std::cout << enemy1->getY();
			std::cout << " ";*/
			//player->setHealth(player->getHealth() - 1);
			//combat(player, enemy1);
			Render();
			/*if (player->getX() + 20 == enemy1->getX() && player->getY() == enemy1->getY() - 2) {
				std::cout << "Collision!";
			}*/

		} 

	};

}

void Game::combat(Entity* player, Entity* enemy) {
	int damage = 0;
	if (player->getAvoid() > enemy->getStrength()) {
		damage = 0;
		std::cout << "Attack missed!";
	}
	else if (player->getAvoid() <= enemy->getStrength()) {
		damage = 20;
		//std::rand;
		//damage calculations, inject some level of randomness
	}
	else {
		damage = 20;
	}
	std::cout << damage;
	int newHealth = player->getHealth() - damage;
	player->setHealth(newHealth);
}

/*void Game::enemyTurn(Entity* enemies[]) {
	for i in enemyonfield :
	loop through enemies, move enemy closer to player until move == 0
	if collision, attack
	if (enemies[i]->getHealth() == 0) {
		//do nothing
	}
	else {

	}
}*/


void Game::Input() {
	SDL_Event event;
	const bool *state	= SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&event)) {
		if (state[SDL_SCANCODE_ESCAPE] || event.type == SDL_EVENT_QUIT) {
			SDL_Quit();
			exit(0);
		}
		/*if (event.type = SDL_EVENT_QUIT) {
			SDL_Quit();
			exit(0);
		}*/
		else {
			if (player->getEntityTurn() == 1) {
				if (state[SDL_SCANCODE_UP] && !(state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_LEFT])) {
					//std::cout << enemy1->getBounds().x << enemy1->getBounds().y;
					player->setSpeed(5);
					player->MoveUp(/*collidables*/);
	
				}
				/*if (state[SDL_SCANCODE_DOWN] && !(state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_LEFT])) {
					player->setSpeed(5);
					player->MoveDown(enemy1->getBounds());
				}
				if (state[SDL_SCANCODE_RIGHT] && !(state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN])) {
					player->setSpeed(5);
					player->MoveRight(enemy1->getBounds());
				}
				if (state[SDL_SCANCODE_LEFT] && !(state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN])) {
					player->setSpeed(5);
					player->MoveLeft(enemy1->getBounds());
				}*/
				if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_DOWN]) {
					player->setSpeed(0);
				}
				if (player->getMove() == 0) {
					player->setTurn(0);
					//EnemyTurn();
				}
			}
			

		}
	}
};


bool Game::renderTextureFromFile(std::string path, const SDL_FRect* srcrect, const SDL_FRect* dstrect) {
	SDL_DestroyTexture(texture);
	texture = nullptr;
	if (SDL_Surface* loadedSurface = IMG_Load(path.c_str()); loadedSurface == nullptr) {
		SDL_Log("Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError());
	}
	else {
		if (texture = SDL_CreateTextureFromSurface(renderer, loadedSurface); texture == nullptr) {
			SDL_Log("Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError());
		}
		else {
			SDL_RenderTexture(renderer, texture, srcrect, dstrect);
		}

		SDL_DestroySurface(loadedSurface);
	}
	return texture != nullptr;
}

void Game::Render() {
	SDL_RenderClear(renderer);
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	renderTextureFromFile("tempmap.png", NULL, NULL);
	SDL_FRect playerRect = { player->getX(), player->getY(), PLAYER_WIDTH, PLAYER_HEIGHT };
	renderTextureFromFile(player->getAsset(), NULL, &playerRect);
	SDL_FRect enemy1Rect = { enemy1->getX(), enemy1->getY(), PLAYER_WIDTH, PLAYER_HEIGHT };
	renderTextureFromFile(enemy1->getAsset(), NULL, &enemy1Rect);
	SDL_FRect escapeRect = { escape->getX(), escape->getY(), PLAYER_WIDTH, PLAYER_HEIGHT };
	renderTextureFromFile(escape->getAsset(), NULL, &escapeRect);
	SDL_FRect ballRect = { temp->getX(), temp->getY(), BALL_SIZE, BALL_SIZE };

	//SDL_RenderFillRect(renderer, &enemy1Rect);
	SDL_RenderFillRect(renderer, &ballRect);
	SDL_RenderDebugText(renderer, 272, 100, "Hello world!");
	SDL_RenderDebugTextFormat(renderer, ((float)(WINDOW_WIDTH - (SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * 46)) / 2), 400, "(This program has been running for %" SDL_PRIu64 " seconds.)", SDL_GetTicks() / 1000);
	
	SDL_RenderPresent(renderer);
	SDL_Delay(50);

};