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

    //void pauseState() override;
    //void resumeState() override;
    //Main loop functions
    void eventHandling(SDLWindow window, Game* manager) override;
    void update(Game* manager, SDLWindow window) override;
    void Render(SDLWindow window) override;
    void update2(SDLWindow window);
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
    //Entity* boulder2;
    Entity* forest1;
    Entity* forest2;
    Entity* forest3;
    Entity* poison1;
    Entity* poison2;
    Entity* escape;
    MIX_Track* movesfx;
    std::vector<Entity*> entities;
    bool poisonflag;
    int temp; 
    int temp2;
    //std::vector<Tile*> tiles; list of interactable tiles
};
