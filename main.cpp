#include "main.h"
#include "Game.h"
#include "LevelTwoState.h"

int main(int argc, char* argv[]) {
	Game game{};
	game.ChangeState(LevelTwoState::Instance());
	while (game.Run()) {
		game.eventHandling();
		game.Update();
		game.Render();
	}
}
