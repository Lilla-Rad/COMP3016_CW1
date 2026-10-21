#pragma once
#include "Constants.h"
#include <SDL3/SDL.h>
#include "Object.h"
#include <vector>


class Entity : public Object {
public:
	Entity(int x, int y, int speed, bool isTurn, bool isPlayer, int health, int avoid, int strength, int move, const std::string asset, SDL_Rect boundaryBox, ObjectType type) : x(x), y(y), speed(speed), isTurn(isTurn), isPlayer(isPlayer), health(health), avoid(avoid), strength(strength), move(move), asset(asset), boundaryBox(boundaryBox), type(type) {};
	void MoveUp(/*std::vector<Object*> colliders*/);
	/*void MoveDown(Object* colliders[]);
	void MoveLeft(Object* colliders[]);
	void MoveRight(Object* colliders[]);*/
	int getX() const { return x; }
	void setX(int xcoord) {
		x = xcoord;
	}
	int getY() const { return y; }
	void setY(int ycoord) {
		y = ycoord;
	}
	int getSpeed() { return speed; }
	void setSpeed(int s) {
		speed = s;
	}
	bool getEntityTurn() { return isTurn; }
	void setTurn(bool t) {
		isTurn = t;
	}
	bool getEntityIdentity() { return isPlayer; }
	void setEntityIdentity(bool i) {
		isPlayer = i;
	}
	int getHealth() { return health; }
	void setHealth(int h) {
		health = h;
	}
	int getAvoid() { return avoid; }
	void setAvoid(int a) {
		avoid = a;
	}
	int getStrength() { return strength; }
	void setStrength(int str) {
		strength = str;
	}
	int getMove() { return move; }
	void setMove(int m) {
		move = m;
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
private:
	int x;
	int y;
	int speed;
	bool isTurn;
	bool isPlayer;
	int health;
	int avoid;
	int strength;
	int move;
	const std::string asset;
	SDL_Rect boundaryBox;
	ObjectType type;
};
