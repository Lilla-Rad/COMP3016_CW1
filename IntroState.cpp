#include "IntroState.h"
#include <iostream>
#include "Constants.h"
#include "SDLWindow.h"
#include "ExitState.h"
#include "TutorialState.h"
#include <SDL3_mixer/SDL_mixer.h>


IntroState IntroState::stateIntro;

bool IntroState::enter()
{
    enemy = new Entity(WINDOW_WIDTH / 2, 0, 5, 1, 20, 10, 10, 4, "whatsss.png", "introvoice.mp3", { WINDOW_WIDTH / 2,0, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::tile);
    intro = 0;
    bool success = true;
    return success;
}

bool IntroState::exit()
{
    return true;
}

void IntroState::eventHandling(SDLWindow window, Game* manager)
{
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_QUIT || e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) {
            manager->ChangeState(ExitState::Instance());
        }
    }
}

void IntroState::update(Game* manager, SDLWindow window)
{
    if (intro == 3) {
        SDL_Delay(2000);
        manager->ChangeState(TutorialState::Instance());
    }

}


void IntroState::Render(SDLWindow window)
{
    SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(window.renderer);
    SDL_SetRenderDrawColor(window.renderer, 255, 255, 255, 255);
    SDL_SetRenderScale(window.renderer, SCALAR * 3, SCALAR * 3);
    if (intro == 0) {
        intro += 1;
    }
    else if (intro == 1) {
        enemy->dialogue(window, "THE KING HAS DECREED IT:", 0, 50);
        intro += 1;
    }
    else if (intro == 2) {
        SDL_RenderDebugText(window.renderer, WINDOW_WIDTH / 60, 32, "THE KING HAS DECREED IT:");
        SDL_RenderDebugText(window.renderer, WINDOW_WIDTH / 60, WINDOW_HEIGHT / 7, "YOU ARE TO DIE.");
        intro += 1;

    }

    SDL_SetRenderScale(window.renderer, SCALAR, SCALAR);

    SDL_RenderPresent(window.renderer);
    SDL_Delay(1000);


}