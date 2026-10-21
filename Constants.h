#pragma once
#include <string>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int TILE_SIZE = (WINDOW_WIDTH * WINDOW_HEIGHT) / 50;
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