#include "ExitState.h"
#include "Constants.h"

//Hollow exit state
ExitState* ExitState::get()
{
    return &sExitState;
}

bool ExitState::enter()
{

    return true;
}

bool ExitState::exit()
{
    return true;
}

void ExitState::eventHandling(SDL_Event& e, SDLWindow window)
{


}

void ExitState::update()
{

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

ExitState ExitState::sExitState;

ExitState::ExitState()
{

}