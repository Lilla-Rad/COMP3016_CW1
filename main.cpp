#include "main.h"
#include "Game.h"
#include "GameOverState.h"

int main(int argc, char* argv[]) {
	Game game{};
	game.ChangeState(GameOverState::Instance());
	while (game.Run()) {
		game.eventHandling();
		game.Update();
		game.Render();
	}
}
