#pragma once
#include "GameState.h"

class ExitState : public GameState
{
public:

    //Transitions
    bool enter() override;
    bool exit() override;

    //Main loop functions
    void eventHandling(SDLWindow window, Game* manager) override;
    void update(Game* manager) override;
    void Render(SDLWindow window) override;

    static ExitState* Instance() {
        return &stateExit;
    }

protected:
    ExitState() {}

private:
    static ExitState stateExit;

};
