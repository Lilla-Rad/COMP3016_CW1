#include "main.h"
#include "Game.h"
#include "LevelOneState.h"

int main(int argc, char* argv[]) {
	Game game{};
	game.ChangeState(LevelOneState::Instance());
	while (game.Run()) {
		game.eventHandling();
		game.Update();
		game.Render();
	}
}
