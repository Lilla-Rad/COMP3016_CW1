#include "LevelOneState.h"
#include <iostream>
#include "Object.h"
#include "Constants.h"
#include "SDLWindow.h"
#include "GameOverState.h"
#include "ExitState.h"



LevelOneState LevelOneState::stateLevelOne;

bool LevelOneState::enter()
{
    bool success = true;
    player = new Entity(0, MAP_HEIGHT / 2, 5, 1, 20, 10, 10, 4, "whatsss.png", "rvoice.mp3", { 0, MAP_HEIGHT / 2, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::player);
    enemy1 = new Entity(WINDOW_WIDTH - PLAYER_WIDTH, MAP_HEIGHT / 2, 5, 0, 20, 20, 20*DIFFICULTY, 4, "pinagaling.png", "pvoice.mp3", { WINDOW_WIDTH - PLAYER_WIDTH, MAP_HEIGHT/2, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::enemy);
    enemy2 = new Entity(3, MAP_HEIGHT-PLAYER_HEIGHT, 5, 0, 20, 20, 20 * DIFFICULTY, 4, "pinagaling.png", "testvoice2.mp3", { 3, MAP_HEIGHT-PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::enemy);
    escape = new Entity(WINDOW_WIDTH-PLAYER_WIDTH, MAP_HEIGHT-PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "pinagaling.png", "testvoice2.mp3", { WINDOW_WIDTH-PLAYER_WIDTH, MAP_HEIGHT-PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::enemy);
    entities.push_back(enemy1);
    entities.push_back(enemy2);
    entities.push_back(escape);

    return success;
}

bool LevelOneState::exit()
{
    return true;
}

void LevelOneState::eventHandling(SDLWindow window, Game* manager)
{
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
        if (player->getMove() > 0 && player->getEntityTurn() == 1) {
            player->playerInput(e);
        }
        else if (player->getMove() <= 0) {
            //enemyturn
            player->setTurn(0);
            std::cout << player->getEntityTurn();
            manager->enemyTurn(entities, player);
        }
        if ((e.type == SDL_EVENT_KEY_DOWN) && (e.key.key == SDLK_RETURN))
        {
            player->dialogue(window, "SHIIIT!", 0, 50);
            std::cout << "kys";

        }
        if (e.type == SDL_EVENT_QUIT || e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) {
            manager->ChangeState(ExitState::Instance());
        }
    }

}

void LevelOneState::update(Game* manager)
{
    if (player->getHealth() <= 0) {
        //proceed to game over; exit for now
        manager->ChangeState(GameOverState::Instance());
    }
    else {
        //for objects on field, check collision
        for (int i = 0; i < entities.size(); ++i) {
            std::cout << entities[i]->getBounds().x;

            /*SDL_FRect intersect;
            if (SDL_GetRectIntersection(player->getBounds(), entities[i]->getBounds(), intersect))*/
            if (manager->collisionCheck(player->getBounds(), entities[i]->getBounds())) {
                if (entities[i]->getType() == ObjectType::enemy) {
                    //move to combat; for now, die instantly
                    player->setHealth(0);
                }
                else if (entities[i]->getType() == ObjectType::escape) {
                    std::cout << "you did it!! wahoo";
                    //move to gamewin
                }
            }
        }
    }

}


void LevelOneState::Render(SDLWindow window)
{
    SDL_RenderClear(window.renderer);
    SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
    SDL_FRect mapRect = { 0, 0, WINDOW_WIDTH, MAP_HEIGHT };
    window.renderTextureFromFile("tempermap.png", NULL, &mapRect);
    SDL_FRect boxRect = { 0, MAP_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT };
    if (player->getEntityTurn()) {
        window.boxRender("PLAYER TURN");
    }
    else {
        window.boxRender("ENEMY TURN");
    }
    /*window.renderTextureFromFile("adachi-rei-machina-mori.png", NULL, &boxRect);
    SDL_SetRenderScale(window.renderer, SCALAR * 2, SCALAR * 2);
    SDL_RenderDebugText(window.renderer, (WINDOW_WIDTH * 0.0125) / (SCALAR * 2), (WINDOW_HEIGHT - BOX_HEIGHT) / (SCALAR * 2) + (BOX_HEIGHT / 3) / (SCALAR * 2), std::to_string(player->getMove()).c_str());
    SDL_SetRenderScale(window.renderer, SCALAR, SCALAR);*/
    player->render(window);
    for (int i = 0; i < entities.size(); ++i) {
        entities[i]->render(window);
    }

    SDL_RenderPresent(window.renderer);
    

}




