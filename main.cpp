#include "main.h"
#include "Game.h"
#include "TitleScreenState.h"

int main(int argc, char* argv[]) {
	Game game{};
	game.ChangeState(TitleScreenState::Instance());
	while (game.Run()) {
		game.eventHandling();
		game.Update();
		game.Render();
	}
}
