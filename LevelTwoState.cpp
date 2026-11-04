#include "LevelTwoState.h"
#include <iostream>
#include "Constants.h"
#include "SDLWindow.h"
#include "GameOverState.h"
#include "ExitState.h"
#include "LevelThreeState.h"
#include <vector>


LevelTwoState LevelTwoState::stateLevelTwo;

bool LevelTwoState::enter()
{
    bool success = true;

    player = new Entity(0, 0, 5, 1, 30, 20, 5, 3, "celestriasprite.png", "testvoice.mp3", { 0, 0, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::player);
    enemy1 = new Entity(0, (MAP_HEIGHT / 2) + PLAYER_HEIGHT, 5, 0, 20, 10, 8 * DIFFICULTY, 4, "soldiersprite.png", "testvoice2.mp3", {0, (MAP_HEIGHT / 2) + PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT}, ObjectType::enemy);
    enemy2 = new Entity(PLAYER_WIDTH * 3, MAP_HEIGHT - PLAYER_HEIGHT, 5, 0, 20, 10, 8 * DIFFICULTY, 4, "soldiersprite.png", "testvoice2.mp3", { PLAYER_WIDTH * 3, MAP_HEIGHT - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::enemy);
    enemy3 = new Entity(PLAYER_WIDTH * 7, MAP_HEIGHT - (PLAYER_HEIGHT * 3), 5, 0, 20, 10, 30 * DIFFICULTY, 3, "knightsprite.png", "testvoice2.mp3", { PLAYER_WIDTH * 7, MAP_HEIGHT - (PLAYER_HEIGHT * 3), PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::enemy);
    poison1 = new Entity(PLAYER_WIDTH*5, 0, 0, 0, 0, 0, 0, 0, "poisontile.png", "", { PLAYER_WIDTH * 5, 0, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    forest1 = new Entity(PLAYER_WIDTH * 5, PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "foresttile.png", "", { PLAYER_WIDTH * 5, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::forest);

    poison2 = new Entity(PLAYER_WIDTH * 10, 0, 0, 0, 0, 0, 0, 0, "poisontile.png", "", { PLAYER_WIDTH * 10, 0, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    poison3 = new Entity(PLAYER_WIDTH * 15, 0, 0, 0, 0, 0, 0, 0, "poisontile.png", "", {PLAYER_WIDTH * 15, 0, PLAYER_WIDTH, PLAYER_HEIGHT}, ObjectType::poison);
    poison4 = new Entity(PLAYER_WIDTH * 20, 0, 0, 0, 0, 0, 0, 0, "poisontile.png", "", { PLAYER_WIDTH * 20, 0, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    poison5 = new Entity(PLAYER_WIDTH * 4, PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "poisontile.png", "", { PLAYER_WIDTH * 4, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    poison6 = new Entity(PLAYER_WIDTH * 8, PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "poisontile.png", "", { PLAYER_WIDTH * 8, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    forest2 = new Entity(PLAYER_WIDTH * 8, 0, 0, 0, 0, 0, 0, 0, "foresttile.png", "", { PLAYER_WIDTH * 8, 0, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::forest);
    forest3 = new Entity(PLAYER_WIDTH * 11, PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "foresttile.png", "", { PLAYER_WIDTH * 11, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::forest);

    poison7 = new Entity(PLAYER_WIDTH * 12, PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "poisontile.png", "", { PLAYER_WIDTH * 12, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    poison8 = new Entity(PLAYER_WIDTH * 16, PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "poisontile.png", "", { PLAYER_WIDTH * 16, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);

    
    escape = new Entity(WINDOW_WIDTH - PLAYER_WIDTH, MAP_HEIGHT /2, 0, 0, 0, 0, 0, 0, "escapetile.png", "", { WINDOW_WIDTH - PLAYER_WIDTH, MAP_HEIGHT/2, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::escape);


    entities.push_back(player);;
    entities.push_back(enemy1);
    entities.push_back(enemy2);
    entities.push_back(enemy3);
    entities.push_back(poison1);
    entities.push_back(forest1);
    entities.push_back(forest2);
    entities.push_back(forest3);
    entities.push_back(poison2);
    entities.push_back(poison3);
    entities.push_back(poison4);
    entities.push_back(poison5);
    entities.push_back(poison6);
    entities.push_back(poison7);
    entities.push_back(poison8);
    entities.push_back(escape);
    check = 0;
    return success;
}

bool LevelTwoState::exit()
{
    for (int i = 0; i < entities.size(); ++i) {
        delete entities[i];
    }
    std::vector<Entity*>().swap(entities);
    return true;
}

void LevelTwoState::eventHandling(SDLWindow window, Game* manager)
{
    SDL_PumpEvents();
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

            player->playerInput(e, entities);
            if (e.key.key == SDLK_UP || e.key.key == SDLK_DOWN || e.key.key == SDLK_LEFT || e.key.key == SDLK_RIGHT) {
                MIX_PlayTrack(movesfx, 0);
            }
            if (player->collisionCheck(player->getBounds(), escape->getBounds())) {
                manager->ChangeState(LevelThreeState::Instance());
            }
        }
        if ((e.type == SDL_EVENT_KEY_DOWN) && (e.key.key == SDLK_RETURN))
        {
            std::string status;
            if (player->getHealth() == 30) {
                status = "I have to get out of here!";
            }
            else if (player->getHealth() <= 15) {
                status = "I have to make it!!";

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

void LevelTwoState::update(Game* manager, SDLWindow window)
{
    SDL_FlushEvents(0x300, 0x400);
    if (player->getHealth() <= 0) {
        window.boxRender("YOU HAVE DIED!");
        SDL_RenderPresent(window.renderer);
        SDL_Delay(2000);
        MIX_StopAllTracks(window.mixer, 0);
        manager->ChangeState(GameOverState::Instance());
    }
    else {
        if (player->collisionCheck(player->getBounds(), escape->getBounds())) {
            manager->ChangeState(LevelThreeState::Instance());
        }
        for (int i = 0; i < entities.size(); ++i) {
            if (entities[i]->getType() == ObjectType::forest && (player->collisionCheck(player->getBounds(), entities[i]->getBounds()))) {
                player->setAvoid(80);
            }
        }
        if (player->getMove() <= 0) {
            //enemyturn
            player->setTurn(0);
            for (int i = 1; i < entities.size() - 1; ++i) {
                if (player->getHealth() <= 0) {
                    break;
                }
                entities[i]->setTurn(1);
                if (entities[i]->getType() == ObjectType::enemy && entities[i]->getHealth() > 0 && entities[i]->getEntityTurn() == 1) {
                    window.boxRender("ENEMY TURN");
                    SDL_RenderPresent(window.renderer);
                    SDL_Delay(1000);
                    int temp = player->getHealth();
                    int temp2 = entities[i]->getHealth();
                    entities[i]->takeTurn(entities, i);
                    window.boxRender("Enemy " + std::to_string(i) + " moves");
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
                        window.boxRender("PLAYER MANAGES TO DEAL " + std::to_string(diff2) + " TO Enemy " + std::to_string(i) + "!");
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
                player->setAvoid(20);
                player->setTurn(1);
                MIX_PlayTrack(movesfx, 0);

            }
        }
    }
}


void LevelTwoState::Render(SDLWindow window)
{
    SDL_RenderClear(window.renderer);
    SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
    SDL_FRect mapRect = { 0, 0, WINDOW_WIDTH, MAP_HEIGHT };
    window.renderTextureFromFile("dirtmap.png", NULL, &mapRect);
    SDL_FRect boxRect = { 0, MAP_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT };
    if (player->getHealth() <= 0) {
        window.boxRender("YOU HAVE DIED!");
    }
    else if (player->getMove() > 0) {
        if (player->getHealth() < 10 && player->getHealth() > 0) {
            window.boxRender("YOU ONLY HAVE " + std::to_string(player->getHealth()) + "HP LEFT!");
        }
        if (check == 0) {
            window.boxRender("You've gotten stronger! Max health up!");
        }
        else {
            window.boxRender("Moves left: " + std::to_string(player->getMove()));

        }
    }

    for (int i = entities.size() - 1; i >= 0; --i) {
        entities[i]->render(window);
    }

    SDL_RenderPresent(window.renderer);

    if (check == 0) {
        std::string sfxPath = "assets//mus//sfx//move.mp3";
        MIX_Audio* sfx = MIX_LoadAudio(window.mixer, sfxPath.c_str(), false);
        movesfx = MIX_CreateTrack(window.mixer);
        MIX_SetTrackAudio(movesfx, sfx);

        std::string sfx2Path = "assets//mus//sfx//damage.mp3";
        MIX_Audio* sfx2 = MIX_LoadAudio(window.mixer, sfx2Path.c_str(), false);
        damagesfx = MIX_CreateTrack(window.mixer);
        MIX_SetTrackAudio(damagesfx, sfx2);
        SDL_Delay(2000);
        check += 1;
    }
}




