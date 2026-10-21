#pragma once
#include "Constants.h"
#include "Object.h"
#include <SDL3/SDL.h>

class Tile : public Object {
public:
	Tile(int x, int y, bool passThrough, bool isUsed, int effect, const std::string asset, SDL_Rect boundaryBox, ObjectType type) : x(x), y(y), passThrough(passThrough), isUsed(isUsed), effect(effect), asset(asset), boundaryBox(boundaryBox), type(type) {};
	int getX() const { return x; }
	int getY() const { return y; }
	bool getPassThrough() { return passThrough; }
	void setPassThrough(bool pt) {
		passThrough = pt;
	}
	bool getTileUse() { return isUsed; }
	void setUsed(bool u) {
		isUsed = u;
	}
	int getEffect() { return effect; }
	void setEffect(int e) {
		effect = e;
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
	//bool collision(Entity* entity, Tile* tile);
	int x;
	int y;
	bool passThrough;
	bool isUsed;
	int effect;
	const std::string asset;
	SDL_Rect boundaryBox;
	ObjectType type;
};

