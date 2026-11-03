#pragma once
#include "GameState.h"

class IntroState : public GameState
{
public:

    //Transitions
    bool enter() override;
    bool exit() override;

    //Main loop functions
    void eventHandling(SDLWindow window, Game* manager) override;
    void update(Game* manager, SDLWindow window) override;
    void Render(SDLWindow window) override;

    static IntroState* Instance() {
        return &stateIntro;
    }


protected:
    IntroState() {}

private:
    //Static instance
    static IntroState stateIntro;
    Entity* enemy;
    int intro;

};

