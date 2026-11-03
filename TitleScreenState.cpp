#include "TitleScreenState.h"
#include <iostream>
#include "Constants.h"
#include "SDLWindow.h"
#include "IntroState.h"
#include "ExitState.h"
#include <SDL3_mixer/SDL_mixer.h>


TitleScreenState TitleScreenState::stateTitleScreen;

bool TitleScreenState::enter()
{
    bool success = true;


    return success;
}

bool TitleScreenState::exit()
{
    return true;
}

void TitleScreenState::eventHandling(SDLWindow window, Game* manager)
{
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_RETURN) {
            SDL_RenderClear(window.renderer);
            manager->ChangeState(IntroState::Instance());
        }
        if (e.type == SDL_EVENT_QUIT || e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) {
            manager->ChangeState(ExitState::Instance());
        }
    }
}


void TitleScreenState::update(Game* manager, SDLWindow window)
{

}


void TitleScreenState::Render(SDLWindow window)
{


    SDL_RenderClear(window.renderer);
    SDL_FRect windowRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    window.renderTextureFromFile("temptitle.png", NULL, &windowRect);
    SDL_SetRenderDrawColor(window.renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_SetRenderScale(window.renderer, SCALAR*2, SCALAR*2);
    SDL_RenderDebugText(window.renderer, PLAYER_WIDTH, MAP_HEIGHT / 5, GAME_TITLE.c_str());
    SDL_SetRenderScale(window.renderer, SCALAR, SCALAR);
    SDL_RenderDebugText(window.renderer, PLAYER_WIDTH*2, MAP_HEIGHT / 2, "PRESS ENTER TO BEGIN");
    SDL_RenderPresent(window.renderer);


}