#include "LevelThreeState.h"
#include <iostream>
#include "Object.h"
#include "Constants.h"
#include "SDLWindow.h"
#include "GameOverState.h"
#include "ExitState.h"
#include "GameWinState.h"
#include <vector>


LevelThreeState LevelThreeState::stateLevelThree;

bool LevelThreeState::enter()
{
    bool success = true;

    player = new Entity(0, MAP_HEIGHT/2, 5, 1, 35, 20, 5, 2, "tempplayer.png", "testvoice.mp3", { 0, MAP_HEIGHT/2, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::player);
    enemy1 = new Entity(0, 0, 5, 0, 20, 10, 40 * DIFFICULTY, 2, "enemyplaceholder.png", "testvoice2.mp3", { 0, 0, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::enemy);
    poison1 = new Entity(PLAYER_WIDTH * 6, (MAP_HEIGHT / 2) + PLAYER_HEIGHT*2, 0, 0, 0, 0, 0, 0, "temppoison.png", "", { PLAYER_WIDTH * 6, (MAP_HEIGHT / 2) + PLAYER_HEIGHT * 2, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    forest1 = new Entity(PLAYER_WIDTH * 5, PLAYER_HEIGHT*2, 0, 0, 0, 0, 0, 0, "tempforest.png", "", { PLAYER_WIDTH * 5, PLAYER_HEIGHT * 2, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::forest);

    poison2 = new Entity(PLAYER_WIDTH * 7, (MAP_HEIGHT / 2) + PLAYER_HEIGHT * 2, 0, 0, 0, 0, 0, 0, "temppoison.png", "", { PLAYER_WIDTH * 7, (MAP_HEIGHT / 2) + PLAYER_HEIGHT * 2, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    poison3 = new Entity(PLAYER_WIDTH * 8, MAP_HEIGHT-PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "temppoison.png", "", { PLAYER_WIDTH * 8, MAP_HEIGHT - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    poison4 = new Entity(PLAYER_WIDTH * 8, (MAP_HEIGHT / 2) + PLAYER_HEIGHT * 2, 0, 0, 0, 0, 0, 0, "temppoison.png", "", { PLAYER_WIDTH * 8, (MAP_HEIGHT / 2) + PLAYER_HEIGHT * 2, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    poison5 = new Entity(PLAYER_WIDTH * 7, (MAP_HEIGHT / 2) + PLAYER_HEIGHT * 3, 0, 0, 0, 0, 0, 0, "temppoison.png", "", { PLAYER_WIDTH * 7, (MAP_HEIGHT / 2) + PLAYER_HEIGHT * 3, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    forest2 = new Entity(PLAYER_WIDTH * 8, PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "tempforest.png", "", { PLAYER_WIDTH * 8, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::forest);
    forest3 = new Entity(PLAYER_WIDTH * 11, 0, 0, 0, 0, 0, 0, 0, "tempforest.png", "", { PLAYER_WIDTH * 11, 0, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::forest);
    boulder = new Entity(PLAYER_WIDTH * 5, (MAP_HEIGHT/2)+PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "tempboulder.png", "", { PLAYER_WIDTH * 5, (MAP_HEIGHT / 2) + PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::boulder);
    poison7 = new Entity(PLAYER_WIDTH * 5, (MAP_HEIGHT/2)-PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "temppoison.png", "", { PLAYER_WIDTH * 5, (MAP_HEIGHT / 2) - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    poison8 = new Entity(PLAYER_WIDTH * 4, MAP_HEIGHT/2, 0, 0, 0, 0, 0, 0, "temppoison.png", "", { PLAYER_WIDTH * 4, MAP_HEIGHT / 2, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    weapon = new Entity(PLAYER_WIDTH*5, MAP_HEIGHT/2, 0, 0, 0, 0, 0, 0, "pinagaling.png", "", { PLAYER_WIDTH * 5, MAP_HEIGHT / 2, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::tile);


    escape = new Entity(WINDOW_WIDTH - PLAYER_WIDTH, 0, 0, 0, 0, 0, 0, 0, "tempescape.png", "", { WINDOW_WIDTH - PLAYER_WIDTH, 0, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::escape);


    entities.push_back(player);;
    entities.push_back(enemy1);
    entities.push_back(poison1);
    entities.push_back(forest1);
    entities.push_back(forest2);
    entities.push_back(forest3);
    entities.push_back(poison2);
    entities.push_back(poison3);
    entities.push_back(poison4);
    entities.push_back(poison5);
    entities.push_back(boulder);
    entities.push_back(poison7);
    entities.push_back(poison8);
    entities.push_back(weapon);
    entities.push_back(escape);
    first = false;
    check = 0;
    return success;
}

bool LevelThreeState::exit()
{
    return true;
}

void LevelThreeState::eventHandling(SDLWindow window, Game* manager)
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
                boulder->MoveRight(entities, 10);
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
                if (player->collisionCheck(player->getBounds(), weapon->getBounds())) {
                    entities.erase(entities.end() - 2);
                    player->setStrength(player->getStrength() + 15);
                    window.boxRender("YOU HAVE FOUND A WEAPON! ATK UP!");
                    SDL_RenderPresent(window.renderer);
                    SDL_Delay(500);
                }
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

void LevelThreeState::update(Game* manager, SDLWindow window)
{

    if (player->getHealth() <= 0) {
        window.boxRender("YOU HAVE DIED!");
        SDL_RenderPresent(window.renderer);
        SDL_Delay(2000);
        MIX_StopAllTracks(window.mixer, 0);
        manager->ChangeState(GameOverState::Instance());
    }
    else {
        if (player->collisionCheck(player->getBounds(), escape->getBounds())) {
            manager->ChangeState(GameWinState::Instance());
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
                    window.boxRender("Enemy " + std::to_string(i) + " moves");
                    entities[i]->setTurn(0);
                    SDL_RenderPresent(window.renderer);

                    SDL_Delay(1000);
                    if (player->getHealth() < temp) {
                        int diff = temp - player->getHealth();

                        window.boxRender("PLAYER TAKES " + std::to_string(diff) + " DAMAGE IN COMBAT!");
                        SDL_RenderPresent(window.renderer);
                        SDL_Delay(2000);
                    }

                    if (entities[i]->getHealth() < temp2) {
                        int diff2 = temp2 - entities[i]->getHealth();
                        window.boxRender("PLAYER MANAGES TO DEAL " + std::to_string(diff2) + " TO Enemy " + std::to_string(i) + "!");
                        SDL_RenderPresent(window.renderer);
                        SDL_Delay(2000);
                    }
                }
                if (entities[i]->getType() == ObjectType::poison && player->collisionCheck(player->getBounds(), entities[i]->getBounds())) {
                    player->setHealth(player->getHealth() - (player->getHealth() * 0.1));
                    bool poisonflag = true;
                    window.boxRender("PLAYER TAKES POISON DAMAGE!");
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
        }
    }
}


void LevelThreeState::Render(SDLWindow window)
{

    std::string sfxPath = "assets//mus//sfx//move.mp3";
    MIX_Audio* sfx = MIX_LoadAudio(window.mixer, sfxPath.c_str(), false);
    movesfx = MIX_CreateTrack(window.mixer);
    MIX_SetTrackAudio(movesfx, sfx);

    SDL_RenderClear(window.renderer);
    SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
    SDL_FRect mapRect = { 0, 0, WINDOW_WIDTH, MAP_HEIGHT };
    window.renderTextureFromFile("temperermap.png", NULL, &mapRect);
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

    SDL_RenderPresent(window.renderer);

    if (check == 0) {
        SDL_Delay(2000);
        check += 1;
    }
}




