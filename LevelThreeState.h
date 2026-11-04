#pragma once
#include <SDL3/SDL.h>
#include "GameState.h"
#include "SDLWindow.h"
#include "Entity.h"
#include <vector>

class LevelThreeState : public GameState
{
public:

    //Transitions
    bool enter() override;
    bool exit() override;

    void eventHandling(SDLWindow window, Game* manager) override;
    void update(Game* manager, SDLWindow window) override;
    void Render(SDLWindow window) override;

    static LevelThreeState* Instance() {
        return &stateLevelThree;
    }


protected:
    LevelThreeState() {}

private:
    //Static instance
    static LevelThreeState stateLevelThree;
    Entity* player;
    Entity* enemy1;
    Entity* poison1;
    Entity* poison2;
    Entity* poison3;
    Entity* poison4;
    Entity* poison5;
    Entity* boulder;
    Entity* poison7;
    Entity* poison8;
    Entity* escape;
    Entity* forest1;
    Entity* forest2;
    Entity* forest3;
    Entity* weapon;
    int check;
    std::vector<Entity*> entities;
    MIX_Track* movesfx;
    MIX_Track* damagesfx;
    MIX_Track* killsfx;
    MIX_Track* bgm;
    SDL_PropertiesID loop;
    //std::vector<Tile*> tiles; list of interactable tiles
};