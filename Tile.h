#pragma once
#include <SDL3/SDL.h>
//#include "SDLWindow.h"
class Tile
{
public:
	Tile(int x, int y, int type);
	void render(/*SDLWindow window*/);
	int getType();
	SDL_Rect getBounds() { return boundaryBox; }

private:
	SDL_Rect boundaryBox;
	int tileType;
};

