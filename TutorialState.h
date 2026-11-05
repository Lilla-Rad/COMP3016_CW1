#pragma once
#include "GameState.h"

class TutorialState: public GameState
{
public:

    //Transitions
    bool enter() override;
    bool exit() override;


    //Main loop functions
    void eventHandling(SDLWindow window, Game* manager) override;
    void update(Game* manager, SDLWindow window) override;
    void Render(SDLWindow window) override;

    static TutorialState* Instance() {
        return &stateTutorial;
    }


protected:
    TutorialState() {}

private:
    //Static instance
    static TutorialState stateTutorial;
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
    std::vector<Entity*> entities;
    int tutorial;
    MIX_Track* movesfx;

};

