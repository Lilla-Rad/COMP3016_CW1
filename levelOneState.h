#pragma once
#include <SDL3/SDL.h>
#include "GameState.h"
#include "SDLWindow.h"
#include "Entity.h"

class LevelOneState : public GameState
{
public:

    //Transitions
    bool enter() override;
    bool exit() override;

    //Main loop functions
    void eventHandling(SDLWindow window, Game* manager) override;
    void update(Game* manager) override;
    void Render(SDLWindow window) override;

    static LevelOneState* Instance() {
        return &stateLevelOne;
    }


protected:
    LevelOneState(){ }

private:
    //Static instance
    static LevelOneState stateLevelOne;
    Entity* player;
    Entity* enemy1;
    Entity* enemy2;
    Entity* boulder;
    Entity* forest1;
    Entity* forest2;
    Entity* forest3;
    Entity* poison1;
    Entity* poison2;
    Entity* escape;
    MIX_Track* track;
    MIX_Track* track2;
    std::vector<Entity*> entities;
    int tutorial;
    bool first;
    int check;
    //std::vector<Tile*> tiles; list of interactable tiles
};
