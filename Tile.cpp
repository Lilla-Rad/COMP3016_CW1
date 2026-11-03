#include "Tile.h"
#include "Constants.h"

Tile::Tile(int x, int y, int type) {
	boundaryBox.x = x;
	boundaryBox.y = y;
	boundaryBox.h = PLAYER_HEIGHT;
	boundaryBox.w = PLAYER_WIDTH;

	tileType = type;
}

void Tile::render(/*SDLWindow window*/) {
	SDL_FRect objRect = { boundaryBox.x, boundaryBox.y, PLAYER_WIDTH, PLAYER_HEIGHT };

	//window.renderTextureFromFile(&tileClips[tileType], NULL, &objRect);
}