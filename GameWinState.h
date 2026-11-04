#pragma once
#include "GameState.h"

class GameWinState : public GameState
{
public:

    //Transitions
    bool enter() override;
    bool exit() override;
    //Main loop functions
    void eventHandling(SDLWindow window, Game* manager) override;
    void update(Game* manager, SDLWindow window) override;
    void Render(SDLWindow window) override;

    static GameWinState* Instance() {
        return &stateGameWin;
    }

protected:
    GameWinState() {}

private:
    static GameWinState stateGameWin;
    Entity* player;
    MIX_Track* track;
    SDL_PropertiesID loop;
};
