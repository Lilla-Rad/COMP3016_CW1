#pragma once
#include "GameState.h"

class GameOverState : public GameState
{
public:

    //Transitions
    bool enter() override;
    bool exit() override;

    //Main loop functions
    void eventHandling(SDLWindow window, Game* manager) override;
    void update(Game* manager) override;
    void Render(SDLWindow window) override;

    static GameOverState* Instance() {
        return &stateGameOver;
    }

protected:
    GameOverState() {}

private:
    static GameOverState stateGameOver;

};
