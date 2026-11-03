#pragma once
#include <string>
#include <stdlib.h>

const std::string GAME_TITLE = "ALL THE BETTER TO HUNT YOU WITH";
const std::string WINDOW_ICON = "assets\\img\\celestriasprite.png";
const std::string BOX_TEXTURE = "banerr.png";
const int BASE_WIDTH = 640;
const int BASE_HEIGHT = 360;
const float SCALAR = 1.0;
const int DIFFICULTY = 1;
const int WINDOW_WIDTH = BASE_WIDTH * SCALAR;
const int WINDOW_HEIGHT = BASE_HEIGHT * SCALAR;
const int MAP_HEIGHT = WINDOW_HEIGHT - (40 * SCALAR);
const int BOX_HEIGHT = WINDOW_HEIGHT - MAP_HEIGHT;
const int TILE_SIZE = (WINDOW_WIDTH * MAP_HEIGHT) / 200;
const int PLAYER_WIDTH = sqrt(TILE_SIZE);
const int PLAYER_HEIGHT = sqrt(TILE_SIZE);


enum class ObjectType {
	player, enemy, escape, forest, boulder, poison, tile, nulltype
};