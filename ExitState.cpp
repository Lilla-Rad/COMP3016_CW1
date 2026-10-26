#include "ExitState.h"
#include "Constants.h"
#include <iostream>

//Hollow exit state
ExitState ExitState::stateExit;

bool ExitState::enter()
{
    return true;
}

bool ExitState::exit()
{
    return true;
}

void ExitState::eventHandling(SDLWindow window, Game* manager)
{
    window.cleanup(window.window, window.renderer, window.texture, window.mixer);

}

void ExitState::update(Game* manager)
{
    manager->Quit();
}

void ExitState::Render(SDLWindow window)
{
    SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
    SDL_SetRenderScale(window.renderer, SCALAR, SCALAR);
    std::string quitMessage = "Quitting";
    for (int i = 0; i < 4; ++i) {
        SDL_RenderDebugText(window.renderer, 5, 5, quitMessage.c_str());
        SDL_Delay(100);
        SDL_RenderPresent(window.renderer);
        quitMessage += ".";
    }
    SDL_SetRenderScale(window.renderer, SCALAR, SCALAR);

}


