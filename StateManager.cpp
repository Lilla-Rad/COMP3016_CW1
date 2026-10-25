#include "StateManager.h"
#include "ExitState.h"

void StateManager::setNextState(GameState* state) {
	if (nextState != ExitState::get()) {
		nextState = state;
	}
	
}

void StateManager::changeState() {
	if (nextState != nullptr) {
		currentState->exit();
		nextState->enter();
		currentState = nextState;
		nextState = nullptr;
	}
}