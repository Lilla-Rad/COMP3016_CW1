#pragma once
#include "GameState.h"

class enemyTurnState: public GameState
{
public:
	static enemyTurnState* get();

	bool enter() override;
	bool exit() override;

	void eventHandling(SDL_Event& e) override;
	void update() override;
	void Render() override;
	void Input();

private:

	static enemyTurnState statePlayerTurn;
	enemyTurnState();


};

