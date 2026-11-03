#include "LevelOneState.h"
#include <iostream>
#include "Constants.h"
#include "SDLWindow.h"
#include "GameOverState.h"
#include "ExitState.h"
#include "GameWinState.h"
#include "LevelTwoState.h"



LevelOneState LevelOneState::stateLevelOne;

bool LevelOneState::enter()
{
    bool success = true;

    player = new Entity(WINDOW_WIDTH/2, 0+(PLAYER_HEIGHT*2), 5, 1, 20, 10, 5, 2, "celestriasprite.png", "testvoice.mp3", {WINDOW_WIDTH / 2, 0 + (PLAYER_HEIGHT * 2), PLAYER_WIDTH, PLAYER_HEIGHT}, ObjectType::player);
    forest1 = new Entity(WINDOW_WIDTH - (PLAYER_WIDTH * 2), MAP_HEIGHT - PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "foresttile.png", "", { WINDOW_WIDTH - (PLAYER_WIDTH * 2), MAP_HEIGHT - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::forest);
    forest2 = new Entity(PLAYER_WIDTH * 4, PLAYER_HEIGHT * 3, 0, 0, 0, 0, 0, 0, "foresttile.png", "", { PLAYER_WIDTH * 4, PLAYER_HEIGHT * 3, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::forest);
    forest3 = new Entity(WINDOW_WIDTH - (PLAYER_WIDTH * 4), PLAYER_HEIGHT * 3, 0, 0, 0, 0, 0, 0, "foresttile.png", "", { WINDOW_WIDTH - (PLAYER_WIDTH * 4), PLAYER_HEIGHT * 3, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::forest);
    enemy1 = new Entity(0, MAP_HEIGHT / 2, 5, 0, 20, 10, 10 * DIFFICULTY, 6, "soldiersprite.png", "testvoice2.mp3", {0, MAP_HEIGHT / 2, PLAYER_WIDTH, PLAYER_HEIGHT}, ObjectType::enemy);
    enemy2 = new Entity(PLAYER_WIDTH*3, MAP_HEIGHT-PLAYER_HEIGHT, 5, 0, 20, 10, 10 * DIFFICULTY, 6, "soldiersprite.png", "testvoice2.mp3", { PLAYER_WIDTH*3, MAP_HEIGHT-PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::enemy);
    boulder = new Entity(WINDOW_WIDTH - PLAYER_WIDTH, MAP_HEIGHT - (PLAYER_HEIGHT*2), 0, 0, 0, 0, 0, 0, "boulder.png", "", { WINDOW_WIDTH - PLAYER_WIDTH, MAP_HEIGHT - PLAYER_HEIGHT * 2, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::boulder);


    poison1 = new Entity(WINDOW_WIDTH - (PLAYER_WIDTH * 3), MAP_HEIGHT - PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "poisontile.png", "", { WINDOW_WIDTH - (PLAYER_WIDTH * 3), MAP_HEIGHT - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    poison2 = new Entity(WINDOW_WIDTH - (PLAYER_WIDTH * 2), MAP_HEIGHT - (PLAYER_HEIGHT*2), 0, 0, 0, 0, 0, 0, "poisontile.png", "", {WINDOW_WIDTH - (PLAYER_WIDTH * 2), MAP_HEIGHT - (PLAYER_HEIGHT * 2), PLAYER_WIDTH, PLAYER_HEIGHT}, ObjectType::poison);

    escape = new Entity(WINDOW_WIDTH-PLAYER_WIDTH, MAP_HEIGHT-PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "escapetile.png", "", { WINDOW_WIDTH-PLAYER_WIDTH, MAP_HEIGHT-PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::escape);
 
    entities.push_back(player);
    entities.push_back(forest1);
    entities.push_back(forest2);
    entities.push_back(forest3);
    entities.push_back(enemy1);
    entities.push_back(enemy2);
    entities.push_back(boulder);
    entities.push_back(poison1);
    entities.push_back(poison2);
    entities.push_back(escape);
    bool first = false;
    int check = 3;
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
        if (e.type == SDL_EVENT_MOUSE_MOTION) {
            for (int i = 0; i < entities.size(); ++i) {
                if (entities[i]->mouseCheck()) {
                    entities[i]->mouseHandling(window);
                }
            }
        }
        if ((e.type == SDL_EVENT_KEY_DOWN) && (e.key.key == SDLK_K) && (player->getMove() == 2) && (player->getEntityTurn() == 1)) {
            if (player->checkForCollidables(entities, 0, 0) == 1) {
                player->checkForCollidables(entities, 0, 1);
                MIX_PlayTrack(movesfx, 0);
                player->setMove(0);
            }
            else if (player->checkForCollidables(entities, 0, 0) == 2) {
                player->checkForCollidables(entities, 0, 0);
            }
        }
        else if (e.type == SDL_EVENT_KEY_DOWN && player->getMove() >= 0 && player->getEntityTurn() == 1) {
            if (player->collisionCheck(player->getBounds(), escape->getBounds())) {
                manager->ChangeState(LevelTwoState::Instance());
            }
            player->playerInput(e, entities);
            if (e.key.key == SDLK_UP || e.key.key == SDLK_DOWN || e.key.key == SDLK_LEFT || e.key.key == SDLK_RIGHT) {
                MIX_PlayTrack(movesfx, 0);
            }
            
        }
        if ((e.type == SDL_EVENT_KEY_DOWN) && (e.key.key == SDLK_RETURN))
        {
            std::string status;
            if (player->getHealth() == 20) {
                status = "I'm scared... but I have to get out of here.";
            }
            else if (player->getHealth() <= 10) {
                status = "Will I make it?";

            }
            else if (player->getHealth() <= 5) {
                status = "It's cold...";
            }
            player->dialogue(window, status, 0, 20);

        }
        if ((e.type == SDL_EVENT_KEY_DOWN) && (e.key.key == SDLK_SPACE))
        {
            window.boxRender("ENDING TURN EARLY...");
            SDL_RenderPresent(window.renderer);
            SDL_Delay(500);
            player->setMove(0);
         
        }
        if (e.type == SDL_EVENT_QUIT || e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) {
            manager->ChangeState(ExitState::Instance());
        }
    }

}

void LevelOneState::update(Game* manager, SDLWindow window)
{
    //check = player->checkForCollidables(entities, 0, 0);
    if (player->getHealth() <= 0) {
        window.boxRender("YOU HAVE DIED!");
        SDL_RenderPresent(window.renderer);
        SDL_Delay(2000);
        MIX_StopAllTracks(window.mixer, 0);
        manager->ChangeState(GameOverState::Instance());
    }
    else {
        if (player->collisionCheck(player->getBounds(), escape->getBounds())) {
            manager->ChangeState(LevelTwoState::Instance());
        }
        for (int i = 0; i < entities.size(); ++i) {
            if (entities[i]->getType() == ObjectType::forest && (player->collisionCheck(player->getBounds(), entities[i]->getBounds()))) {
                player->setAvoid(80);
            }
            else {
                player->setAvoid(10);
            }
        }
        if (player->getMove() <= 0) {
            //enemyturn
            player->setTurn(0);
            //pause this state, push state enemy turn onto stack and then resume? maybe?
            for (int i = 1; i < entities.size() - 1; ++i) {
                if (player->getHealth() <= 0) {
                    break;
                }
                entities[i]->setTurn(1);
                if (entities[i]->getType() == ObjectType::forest && (player->collisionCheck(player->getBounds(), entities[i]->getBounds()))) {
                    player->setAvoid(80);
                }
                if (entities[i]->getType() == ObjectType::enemy && entities[i]->getHealth() > 0 && entities[i]->getEntityTurn() == 1) {
                    window.boxRender("ENEMY TURN");
                    SDL_RenderPresent(window.renderer);
                    SDL_Delay(1000);
                    int temp = player->getHealth();
                    int temp2 = entities[i]->getHealth();
                    entities[i]->takeTurn(entities, i);
                    window.boxRender("Enemy " + std::to_string(i - 3) + " moves");
                    entities[i]->setTurn(0);
                    SDL_RenderPresent(window.renderer);

                    SDL_Delay(1000);
                    if (player->getHealth() < temp) {
                        int diff = temp - player->getHealth();

                        window.boxRender("PLAYER TAKES " + std::to_string(diff) + " DAMAGE IN COMBAT!");
                        MIX_PlayTrack(damagesfx, 0);
                        SDL_RenderPresent(window.renderer);
                        SDL_Delay(2000);
                    }

                    if (entities[i]->getHealth() < temp2) {
                        int diff2 = temp2 - entities[i]->getHealth();
                        window.boxRender("PLAYER DEALS " + std::to_string(diff2) + " TO Enemy " + std::to_string(i - 3) + " IN TURN!");
                        MIX_PlayTrack(damagesfx, 0);
                        SDL_RenderPresent(window.renderer);
                        SDL_Delay(2000);
                    }
                }
                if (entities[i]->getType() == ObjectType::poison && player->collisionCheck(player->getBounds(), entities[i]->getBounds())) {
                    player->setHealth(player->getHealth() - (player->getHealth() * 0.1));
                    bool poisonflag = true;
                    window.boxRender("PLAYER TAKES POISON DAMAGE!");
                    MIX_PlayTrack(damagesfx, 0);
                    SDL_RenderPresent(window.renderer);
                    SDL_Delay(500);
                }

            }
            if (player->getHealth() <= 0) {
                window.boxRender("YOU HAVE DIED!");
                SDL_RenderPresent(window.renderer);
                SDL_Delay(2000);
                MIX_StopAllTracks(window.mixer, 0);
                manager->ChangeState(GameOverState::Instance());
            }
            else {
                player->setMove(2);
                SDL_RenderPresent(window.renderer);
                SDL_Delay(1000);

                window.boxRender("PLAYER TURN");
                SDL_RenderPresent(window.renderer);
                SDL_Delay(500);
                player->setTurn(1);
                MIX_PlayTrack(movesfx, 0);

            }
            //manager->enemyTurn(entities, player);
        }
    }

}


void LevelOneState::Render(SDLWindow window)
{
    std::string sfxPath = "assets//mus//sfx//move.mp3";
    MIX_Audio* sfx = MIX_LoadAudio(window.mixer, sfxPath.c_str(), false);
    movesfx = MIX_CreateTrack(window.mixer);
    MIX_SetTrackAudio(movesfx, sfx);
    std::string sfx2Path = "assets//mus//sfx//damage.mp3";
    MIX_Audio* sfx2 = MIX_LoadAudio(window.mixer, sfx2Path.c_str(), false);
    damagesfx = MIX_CreateTrack(window.mixer);
    MIX_SetTrackAudio(damagesfx, sfx2);
    SDL_RenderClear(window.renderer);
    SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
    SDL_FRect mapRect = { 0, 0, WINDOW_WIDTH, MAP_HEIGHT };
    window.renderTextureFromFile("dirtmap.png", NULL, &mapRect);
    SDL_FRect boxRect = { 0, MAP_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT };
    //move mouse handling into an entity method? do after collision
    if (player->getHealth() <= 0) {
        window.boxRender("YOU HAVE DIED!");
    }
    else if (player->getMove() > 0) {
        if (player->getHealth() < 10 && player->getHealth() > 0) {
            window.boxRender("YOU ONLY HAVE " + std::to_string(player->getHealth()) + "HP LEFT!");
        }
        else {
            switch (player->checkForCollidables(entities, 0, 0)) {
            case 1:
                window.boxRender("PRESS K TO MOVE BOULDER (USE ALL MOVES)");
                break;
            case 3:
                window.boxRender("Moves left: " + std::to_string(player->getMove()));
                break;
            }
        }
    }

    for (int i = entities.size() - 1; i >= 0; --i) {
        entities[i]->render(window);

    }

    //maybe render in reverse order? render player on top of terrain ideally


    SDL_RenderPresent(window.renderer); 

}




