#include "LevelOneState.h"
#include <iostream>
#include "Constants.h"
#include "SDLWindow.h"




//IntoState Implementation
LevelOneState* LevelOneState::get()
{
    //Get static instance
    return &stateLevelOne;
}

bool LevelOneState::enter()
{
    //Loading success flag
    bool success = true;
    std::cout << "fml";
    player = new Entity(0, (MAP_HEIGHT / 2) / SCALAR, 5, 1, 1, 20, 10, 10, 9999999999, "whatsss.png", "rvoice.mp3", { 0, (MAP_HEIGHT / 2) / int(SCALAR), PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::player);

    return success;
}

bool LevelOneState::exit()
{
    return true;
}

void LevelOneState::eventHandling(SDL_Event& e, SDLWindow window)
{
    if ((e.type == SDL_EVENT_KEY_DOWN) && (e.key.key == SDLK_RETURN))
    {
        player->dialogue(window, "SHIIIT!", 0, 50);
        std::cout << "kys";
        
    }
}

void LevelOneState::update()
{
    //check collision

}

void LevelOneState::Render(SDLWindow window)
{
    SDL_RenderClear(window.renderer);
    SDL_SetRenderDrawColor(window.renderer, 255, 255, 255, 255);
    SDL_FRect mapRect = { 0, 0, WINDOW_WIDTH / SCALAR, MAP_HEIGHT / SCALAR };
    window.renderTextureFromFile("tempermap.png", NULL, &mapRect);
    SDL_FRect boxRect = { 0, MAP_HEIGHT / SCALAR, WINDOW_WIDTH / SCALAR, WINDOW_HEIGHT / SCALAR };
    window.renderTextureFromFile("adachi-rei-machina-mori.png", NULL, &boxRect);
    player->render(window);

    SDL_RenderPresent(window.renderer);
    

}

//static instance
LevelOneState LevelOneState::stateLevelOne;

LevelOneState::LevelOneState()
{
}

