#include "LevelOneState.h"
#include <iostream>
#include "Object.h"
#include "Constants.h"
#include "SDLWindow.h"
#include "GameOverState.h"
#include "ExitState.h"
#include "GameWinState.h"



LevelOneState LevelOneState::stateLevelOne;

bool LevelOneState::enter()
{
    bool success = true;
    MIX_Mixer* mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);

    std::string musicPath = "assets//mus//bgm//placeholderbattle.mp3";
    MIX_Audio* bgm = MIX_LoadAudio(mixer, musicPath.c_str(), false);
    MIX_Track* track = MIX_CreateTrack(mixer);
    std::string sfxPath = "assets//mus//bgm//move.mp3";
    MIX_Audio* sfx = MIX_LoadAudio(mixer, musicPath.c_str(), false);
    MIX_Track* track2 = MIX_CreateTrack(mixer);
    MIX_SetTrackAudio(track, bgm);
    MIX_SetTrackAudio(track2, sfx);
    

    player = new Entity(WINDOW_WIDTH/2, 0, 5, 1, 20, 10, 10, 4, "tempplayer.png", "testvoice.mp3", { WINDOW_WIDTH/2, MAP_HEIGHT , PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::player);
    enemy1 = new Entity(/*WINDOW_WIDTH - PLAYER_WIDTH*/0, MAP_HEIGHT / 2, 5, 0, 20, 20, 20 * DIFFICULTY, 6, "enemyplaceholder.png", "testvoice2.mp3", {0, MAP_HEIGHT / 2, PLAYER_WIDTH, PLAYER_HEIGHT}, ObjectType::enemy);
    enemy2 = new Entity(PLAYER_WIDTH*3, MAP_HEIGHT-PLAYER_HEIGHT, 5, 0, 20, 20, 20 * DIFFICULTY, 6, "enemyplaceholder.png", "testvoice2.mp3", { PLAYER_WIDTH*3, MAP_HEIGHT-PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::enemy);
    boulder = new Entity(WINDOW_WIDTH - PLAYER_WIDTH, MAP_HEIGHT - (PLAYER_HEIGHT*2), 0, 0, 0, 0, 0, 0, "tempboulder.png", "", { WINDOW_WIDTH - PLAYER_WIDTH, MAP_HEIGHT - PLAYER_HEIGHT * 2, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::boulder);
    forest1 = new Entity(WINDOW_WIDTH - (PLAYER_WIDTH*2), MAP_HEIGHT - PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "tempforest.png", "", { WINDOW_WIDTH - (PLAYER_WIDTH * 2), MAP_HEIGHT - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::forest);
    forest2 = new Entity(PLAYER_WIDTH * 4, PLAYER_HEIGHT*3, 0, 0, 0, 0, 0, 0, "tempforest.png", "", { PLAYER_WIDTH * 4, PLAYER_HEIGHT * 3, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::forest);
    forest3 = new Entity(WINDOW_WIDTH - (PLAYER_WIDTH * 4), PLAYER_HEIGHT * 3, 0, 0, 0, 0, 0, 0, "tempforest.png", "", { WINDOW_WIDTH - (PLAYER_WIDTH * 4), PLAYER_HEIGHT * 3, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::forest);
    poison1 = new Entity(WINDOW_WIDTH - (PLAYER_WIDTH * 3), MAP_HEIGHT - PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "temppoison.png", "", { WINDOW_WIDTH - (PLAYER_WIDTH * 3), MAP_HEIGHT - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    poison2 = new Entity(WINDOW_WIDTH - (PLAYER_WIDTH * 2), MAP_HEIGHT - (PLAYER_HEIGHT*2), 0, 0, 0, 0, 0, 0, "temppoison.png", "", {WINDOW_WIDTH - (PLAYER_WIDTH * 2), MAP_HEIGHT - (PLAYER_HEIGHT * 2), PLAYER_WIDTH, PLAYER_HEIGHT}, ObjectType::poison);

    escape = new Entity(WINDOW_WIDTH-PLAYER_WIDTH, MAP_HEIGHT-PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "tempescape.png", "", { WINDOW_WIDTH-PLAYER_WIDTH, MAP_HEIGHT-PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::escape);
 
    entities.push_back(player);
    entities.push_back(enemy1);
    entities.push_back(enemy2);
    entities.push_back(boulder);
    entities.push_back(forest1);
    entities.push_back(forest2);
    entities.push_back(forest3);
    entities.push_back(poison1);
    entities.push_back(poison2);
    entities.push_back(escape);
    int tutorial = 0;
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
    /*if (tutorial == 2) {
        player->dialogue(window, "Please, just leave me alone!", 1, 70);
        player->dialogue(window, "Move with <- ^ -> v", 1, 50);
        tutorial += 1;
    }*/
    //change to switch statement
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_MOUSE_MOTION) {
            if (tutorial == 0) {
                player->dialogue(window, "Please, just leave me alone!", 0, 30);
                tutorial += 1;
            }
            for (int i = 0; i < entities.size(); ++i) {
                if (entities[i]->mouseCheck() && (entities[i]->getType() == ObjectType::enemy || entities[i]->getType() == ObjectType::player)) {
                    bool moused = true;
                    //manager->mouseHandling(entities[i]);
                    window.boxRender("Current health: " + std::to_string(entities[i]->getHealth()));
                    SDL_RenderPresent(window.renderer);
                    SDL_Delay(500);
                }
            }
        }
        else if ((e.type == SDL_EVENT_KEY_DOWN) && (e.key.key == SDLK_K) && (player->getMove() == 2) && (player->getEntityTurn() == 1)) {
            boulder->MoveLeft(entities, 3);
            MIX_PlayTrack(track2, 0);
            player->setMove(0);
        }
        else if (e.type == SDL_EVENT_KEY_DOWN && player->getMove() > 0 && player->getEntityTurn() == 1) {
            if (tutorial == 8) {
                
                tutorial += 1;
            }
            player->takeTurn(e, entities, 0, window);
            MIX_PlayTrack(track2, 0);
            
        }
        else if (player->getMove() <= 0) {
            //enemyturn
            player->setTurn(0);
            window.boxRender("ENEMY TURN");
            SDL_RenderPresent(window.renderer);
            SDL_Delay(500);
            //pause this state, push state enemy turn onto stack and then resume? maybe?
            for (int i = 1; i < entities.size() - 1; ++i) {
                entities[i]->setTurn(1);
                if (entities[i]->getType() == ObjectType::enemy && entities[i]->getHealth() > 0 && entities[i]->getEntityTurn() == 1) {
                    int temp = player->getHealth();
                    
                    entities[i]->takeTurn(e, entities, i, window);
                    window.boxRender("Enemy " + std::to_string(i) + " moves");
                    entities[i]->setTurn(0);
                    MIX_PlayTrack(track2, 0);
                    SDL_RenderPresent(window.renderer);
                    SDL_Delay(1000);
                    if (player->getHealth() < temp) {
                        int diff = temp - player->getHealth();
                        window.boxRender("PLAYER TAKES " + std::to_string(diff) + " DAMAGE IN COMBAT!");
                        SDL_RenderPresent(window.renderer);
                        SDL_Delay(2000);
                    }
                }
                if (entities[i]->getType() == ObjectType::poison && player->collisionCheck(player->getBounds(), entities[i]->getBounds())) {
                    player->setHealth(player->getHealth() - (player->getHealth() * 0.1));
                    window.boxRender("PLAYER TAKES POISON DAMAGE!");
                    SDL_RenderPresent(window.renderer);
                    SDL_Delay(500);

                }
            }
            player->setMove(2);

            if (player->getHealth() < 10 && player->getHealth() > 0) {
                window.boxRender("YOU ONLY HAVE " + std::to_string(player->getHealth()) + "HP LEFT!");
            }
            else if (player->getHealth() <= 0) {
                window.boxRender("YOU WERE FELLED IN COMBAT!");
            }
            SDL_RenderPresent(window.renderer);
            SDL_Delay(1000);
            
            window.boxRender("PLAYER TURN");
            SDL_RenderPresent(window.renderer);
            SDL_Delay(500);
            player->setTurn(1);
            //manager->enemyTurn(entities, player);
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
            if (tutorial == 3) {
                player->dialogue(window, "Phew... did I lose them?", 0, 50);
                SDL_Delay(500);
                tutorial += 1;
            }
            else if (tutorial == 4) {
                enemy1->dialogue(window, "STOP RIGHT THERE!", 0, 50);
                tutorial += 1;
            }
            else if (tutorial == 5) {
                enemy2->dialogue(window, "Get back here!!", 0, 50);
                tutorial += 1;
            }
            else if (tutorial == 6) {
                player->dialogue(window, "EEP!", 0, 30);
                tutorial += 1;
            }
            else if (tutorial == 7) {
                escape->render(window);
                SDL_Delay(500);
                player->dialogue(window, "If I make it there, I should be safe...", 0, 50);
                MIX_PlayTrack(track, 0);
                tutorial += 1;
            }
            else {
                window.boxRender("ENDING TURN EARLY...");
                SDL_RenderPresent(window.renderer);
                SDL_Delay(500);
                player->setMove(0);
            }

        }
        if (e.type == SDL_EVENT_QUIT || e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) {
            manager->ChangeState(ExitState::Instance());
        }
    }

}

void LevelOneState::update(Game* manager)
{
    check = player->checkForCollidables(entities, 0, 0);
    if (player->getHealth() <= 0) {
        manager->ChangeState(GameOverState::Instance());
    }
    else {
        if (player->collisionCheck(player->getBounds(), escape->getBounds())) {
            manager->ChangeState(GameWinState::Instance());
        }
        for (int i = 0; i < entities.size(); ++i) {
            if (entities[i]->getType() == ObjectType::forest && (player->collisionCheck(player->getBounds(), entities[i]->getBounds()))) {
                player->setAvoid(30);
            }
            else {
                player->setAvoid(10);
            }
        }
        //for objects on field, check collision
        /*for (int i = 1; i < entities.size(); ++i) {

            SDL_FRect intersect;
            if (SDL_GetRectIntersection(player->getBounds(), entities[i]->getBounds(), intersect))
            if (manager->collisionCheck(player->getBounds(), entities[i]->getBounds(), entities[i]->getType())) {
                if (!(entities[i]->getType() == ObjectType::escape)) {
                    manager->collisionHandling(player, entities[i]);
                }
                else {
                    manager->ChangeState(GameWinState::Instance());
                }
                /*if (entities[i]->getType() == ObjectType::enemy) {
                    //move to combat; for now, die instantly
                    player->setHealth(0);
                }
                else if (entities[i]->getType() == ObjectType::escape) {
                    std::cout << "you did it!! wahoo";
                    //move to gamewin
                }
            }
        }*/
    }

}


void LevelOneState::Render(SDLWindow window)
{
    SDL_RenderClear(window.renderer);
    SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
    SDL_FRect mapRect = { 0, 0, WINDOW_WIDTH, MAP_HEIGHT };
    window.renderTextureFromFile("tempermap.png", NULL, &mapRect);
    SDL_FRect boxRect = { 0, MAP_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT };
    //move mouse handling into an entity method? do after collision
    if (tutorial < 3) {
        window.boxRender("");
    }
    else if (tutorial < 8) {
        window.boxRender("Press SPACE to continue");
    }
    else if (tutorial < 9) {
        window.boxRender("Move with < \u005e > v");
    }
    else {
        switch (player->checkForCollidables(entities, 0, 0)) {
        case 1:
            window.boxRender("PRESS K TO MOVE BOULDER (USE ALL MOVES)");
            break;
        case 2:
            window.boxRender("PRESS K TO INITIATE COMBAT");
            break;
        case 3:
            window.boxRender("Moves left: " + std::to_string(player->getMove()));
        }
    }
    /*for (int i = 0; i < entities.size(); ++i) {
        if (player->checkForCollidables(entities, 0, 0) == 1) {
            window.boxRender("PRESS K TO MOVE BOULDER");
        }
        else if (player->checkForCollidables(entities, 0, 0) == 2) {
            window.boxRender("PRESS K TO INITIATE COMBAT");
        }
        else if (player->checkForCollidables(entities, 0, 0) == 3 && player->getEntityTurn() && !(entities[i]->mouseCheck())) {
            window.boxRender("Moves left: " + std::to_string(player->getMove()));
        }
        else if (entities[i]->mouseCheck()) {
            window.boxRender("Current health: " + std::to_string(entities[i]->getHealth()));
            SDL_Delay(500);
        }
    }*/



    /*if (player->getEntityTurn() && !(player->mouseCheck())) {
        window.boxRender("PLAYER TURN");
    }
    else {
        for (int i = 0; i < entities.size(); ++i) {
            if (entities[i]->mouseCheck() && (entities[i]->getType() == ObjectType::enemy || entities[i]->getType() == ObjectType::player)) {
                window.boxRender("Current health: " + std::to_string(entities[i]->getHealth()));
            }
        }
    }*/

    /*window.renderTextureFromFile("adachi-rei-machina-mori.png", NULL, &boxRect);
    SDL_SetRenderScale(window.renderer, SCALAR * 2, SCALAR * 2);
    SDL_RenderDebugText(window.renderer, (WINDOW_WIDTH * 0.0125) / (SCALAR * 2), (WINDOW_HEIGHT - BOX_HEIGHT) / (SCALAR * 2) + (BOX_HEIGHT / 3) / (SCALAR * 2), std::to_string(player->getMove()).c_str());
    SDL_SetRenderScale(window.renderer, SCALAR, SCALAR);*/
    //player->render(window);
    if (tutorial >= 8) {
        for (int i = entities.size() - 1; i >= 0; --i) {
            entities[i]->render(window);
        }
    }
    else if (tutorial > 3) {
        for (int i = entities.size() - 2; i >= 0; --i) {
            entities[i]->render(window);
        }
    }
    else {
        player->render(window);
    }

    //maybe render in reverse order? render player on top of terrain ideally


    SDL_RenderPresent(window.renderer); 

    if (tutorial > 0 && tutorial < 3) {
        player->render(window);
        player->MoveDown(entities, 0);
        SDL_Delay(500);
        tutorial += 1;
        if (tutorial == 3) {
            first = true;
        }
    }

}




