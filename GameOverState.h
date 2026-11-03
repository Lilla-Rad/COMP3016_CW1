#pragma once
#include "GameState.h"

class GameOverState : public GameState
{
public:

    //Transitions
    bool enter() override;
    bool exit() override;

    //void pauseState() override;
    //void resumeState() override;
    //Main loop functions
    void eventHandling(SDLWindow window, Game* manager) override;
    void update(Game* manager, SDLWindow window) override;
    void Render(SDLWindow window) override;

    static GameOverState* Instance() {
        return &stateGameOver;
    }

protected:
    GameOverState() {}

private:
    static GameOverState stateGameOver;
    MIX_Track* track;

};
