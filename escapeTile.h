#pragma once
#include "Tile.h"

class escapeTile : public Tile
{
	using Tile::Tile;
	void escapeWin();
};

