#pragma once
#include "GameState.h"

class playerTurnState : public GameState
{
public:
	static playerTurnState* get();

	bool enter() override;
	bool exit() override;

	void eventHandling(SDL_Event& e) override;
	void update() override;
	void Render() override;
	void Input();

private:

	static playerTurnState statePlayerTurn;
	playerTurnState();


};

