#pragma once
#include <string>
#include <stdlib.h>

const int BASE_WIDTH = 640;
const int BASE_HEIGHT = 360;
const float SCALAR = 1.0;
const int WINDOW_WIDTH = BASE_WIDTH * SCALAR;
const int WINDOW_HEIGHT = BASE_HEIGHT * SCALAR;
const int LVL1_WIDTH = WINDOW_WIDTH;
const int LVL1_HEIGHT = WINDOW_HEIGHT;
const int MAP_HEIGHT = WINDOW_HEIGHT - (40 * SCALAR);
const int BOX_HEIGHT = WINDOW_HEIGHT - MAP_HEIGHT;
const int TILE_SIZE = (WINDOW_WIDTH * MAP_HEIGHT) / 200;
const int PADDLE_WIDTH = 100;
const int PADDLE_HEIGHT = 100;
const int PLAYER_WIDTH = sqrt(TILE_SIZE);
const int PLAYER_HEIGHT = sqrt(TILE_SIZE);
const int BALL_SIZE = 100;
const int BALL_SPEED = 5;
const int PADDLE_SPEED = TILE_SIZE;
//const char* MAP_PATH = "adachi-rei-machina-mori.png";
const std::string PLAYER_PATH = "adachi-rei-machina-mori.png";
const std::string ENEMY_PATH = "adachi-rei-machina-mori.png";


enum class ObjectType {
	player, enemy, escape, forest, boulder, poison, tile, nulltype
};