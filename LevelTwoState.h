#pragma once
#include <SDL3/SDL.h>
#include "GameState.h"
#include "SDLWindow.h"
#include "Entity.h"
#include <vector>

class LevelTwoState : public GameState
{
public:

    //Transitions
    bool enter() override;
    bool exit() override;

    void eventHandling(SDLWindow window, Game* manager) override;
    void update(Game* manager, SDLWindow window) override;
    void Render(SDLWindow window) override;

    static LevelTwoState* Instance() {
        return &stateLevelTwo;
    }


protected:
    LevelTwoState() {}

private:
    //Static instance
    static LevelTwoState stateLevelTwo;
    Entity* player;
    Entity* enemy1;
    Entity* enemy2;
    Entity* enemy3;
    Entity* poison1;
    Entity* poison2;
    Entity* poison3;
    Entity* poison4;
    Entity* poison5;
    Entity* poison6;
    Entity* poison7;
    Entity* poison8;
    Entity* escape;

    Entity* forest1;

    Entity* forest2;
    Entity* forest3;
    bool first;
    int check;
    std::vector<Entity*> entities;
    MIX_Track* movesfx;
    MIX_Track* damagesfx;
    //std::vector<Tile*> tiles; list of interactable tiles
};