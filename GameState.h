#pragma once
#include <SDL3/SDL.h>
#include "Entity.h"
#include "escapeTile.h"

class GameState
{
public:
	virtual bool enter() = 0;
	virtual bool exit() = 0;
	virtual void eventHandling(SDL_Event& e) = 0;
	virtual void update() = 0;
	virtual void Render() = 0;
		
	virtual	~GameState() = default;
	
	
protected:
	void combat(Entity* a, Entity* b);
	Entity* player;
	Entity* enemy;
	escapeTile* escape;
	int level;

};

