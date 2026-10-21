#pragma once
#include "Entity.h"
#include "Ball.h"
#include "Constants.h"
#include "escapeTile.h"
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>

class Game {

public:
	Game();
	~Game();
	void Run();
private:
	//game loop
	void Input();
	bool init();
	//ObjectType type;
	Entity* player;
	Entity* enemy1;
	escapeTile* escape;
	//bool collisionCheck(SDL_Rect a, SDL_Rect b);
	/*Entity* enemy2;
	Entity* enemy3;*/
	Ball* ball;
	int level;
	//rendering
	void levelSetup(int level);
	void Render();
	void gameOver();
	void gameWin();
	void enemyTurn(Entity* enemies[]);
	void combat(Entity* player, Entity* enemy);
	bool renderTextureFromFile(std::string path, const SDL_FRect* srcrect, const SDL_FRect* dstrect);
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	MIX_Mixer* mixer;
	//Object* collidables[];
	std::vector<Object*> collidables;

};