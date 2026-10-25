#pragma once
#include "GameState.h"

class ExitState : public GameState
{
public:
    //Static accessor
    static ExitState* get();

    //Transitions
    bool enter() override;
    bool exit() override;

    //Main loop functions
    void eventHandling(SDL_Event& e, SDLWindow window) override;
    void update() override;
    void Render(SDLWindow window) override;

private:
    //Static instance
    static ExitState sExitState;

    //Private constructor
    ExitState();
};
