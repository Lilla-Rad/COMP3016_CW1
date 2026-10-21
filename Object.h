#pragma once
#include <SDL3/SDL.h>
#include "Constants.h"
#include <string>

class Object {
public:
	bool collisionCheck(SDL_Rect a, SDL_Rect b);
	void handleCollision(Object* objectA, Object* objectB);
	int getX() const { return x; }
	void setX(int xcoord) {
		x = xcoord;
	}
	int getY() const { return y; }
	void setY(int ycoord) {
		y = ycoord;
	}
	const std::string getAsset() { return asset; }
	void setAsset(const std::string ass) {
		asset == ass;
	}
	SDL_Rect getBounds() { return boundaryBox; }
	void setBounds(SDL_Rect bounds) {
		boundaryBox = bounds;
	}
	ObjectType getType() { return type; }
	void setType(ObjectType obj) {
		type = obj;
	}
protected:
	int x;
	int y;
	const std::string asset;
	SDL_Rect boundaryBox;
	ObjectType type;
};

