#include "main.h"
#include "Game.h"
#include "TutorialState.h"

int main(int argc, char* argv[]) {
	Game game{};
	game.ChangeState(TutorialState::Instance());
	while (game.Run()) {
		game.eventHandling();
		game.Update();
		game.Render();
	}
}
