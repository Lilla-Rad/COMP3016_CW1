#pragma once
#include "SDLWindow.h"
#include "Object.h"

class Entity : public Object
{
public:
	Entity(int x, int y, int speed, bool isTurn, int health, int avoid, int strength, int move, const std::string asset, std::string voice, SDL_Rect boundaryBox, ObjectType type) : x(x), y(y), speed(speed), isTurn(isTurn), health(health), avoid(avoid), strength(strength), move(move), asset(asset), voice(voice), boundaryBox(boundaryBox), type(type) {};	
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void render(SDLWindow window);
	void playerInput(SDL_Event& e);
	void dialogue(SDLWindow window, std::string speech, bool pos, int delay);
	void Die();
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
	std::string getVoice() { return voice; }
	void setVoice(std::string voi) {
		voice == voi;
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
	int health;
	int avoid;
	int strength;
	int move;
	const std::string asset;
	std::string voice;
	SDL_Rect boundaryBox;
	ObjectType type;
};

