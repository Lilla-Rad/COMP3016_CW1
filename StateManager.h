#pragma once
#include <vector>
#include "GameState.h"

class StateManager
{
public:
	void setNextState(GameState* nextState);
	void changeState();
	GameState* currentState;
	GameState* nextState;
};

