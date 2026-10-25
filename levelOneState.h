#pragma once
#include <SDL3/SDL.h>
#include "GameState.h"
#include "SDLWindow.h"
#include "Entity.h"

class LevelOneState : public GameState
{
public:
    //Static accessor
    static LevelOneState* get();

    //Transitions
    bool enter() override;
    bool exit() override;

    //Main loop functions
    void eventHandling(SDL_Event& e, SDLWindow window) override;
    void update() override;
    void Render(SDLWindow window) override;

private:
    //Static instance
    static LevelOneState stateLevelOne;
    Entity* player;
    
    //Private constructor
    LevelOneState();

};
