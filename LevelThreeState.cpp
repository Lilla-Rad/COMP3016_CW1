#include "LevelThreeState.h"
#include <iostream>
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

    player = new Entity(0, MAP_HEIGHT/2, 5, 1, 35, 20, 5, 4, "celestriasprite.png", "celestriavoice.mp3", { 0, MAP_HEIGHT/2, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::player);
    enemy1 = new Entity(0, 0, 5, 0, 40, 10, 40 * DIFFICULTY, 1, "paladinsprite.png", "enemyvoice.mp3", { 0, 0, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::enemy);
    poison1 = new Entity(PLAYER_WIDTH * 6, (MAP_HEIGHT / 2) + PLAYER_HEIGHT*2, 0, 0, 0, 0, 0, 0, "poisontile.png", "", { PLAYER_WIDTH * 6, (MAP_HEIGHT / 2) + PLAYER_HEIGHT * 2, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    forest1 = new Entity(PLAYER_WIDTH * 5, PLAYER_HEIGHT*2, 0, 0, 0, 0, 0, 0, "foresttile.png", "", { PLAYER_WIDTH * 5, PLAYER_HEIGHT * 2, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::forest);

    poison2 = new Entity(PLAYER_WIDTH * 7, (MAP_HEIGHT / 2) + PLAYER_HEIGHT * 2, 0, 0, 0, 0, 0, 0, "poisontile.png", "", { PLAYER_WIDTH * 7, (MAP_HEIGHT / 2) + PLAYER_HEIGHT * 2, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    poison3 = new Entity(PLAYER_WIDTH * 8, MAP_HEIGHT-PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "poisontile.png", "", { PLAYER_WIDTH * 8, MAP_HEIGHT - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    poison4 = new Entity(PLAYER_WIDTH * 8, (MAP_HEIGHT / 2) + PLAYER_HEIGHT * 2, 0, 0, 0, 0, 0, 0, "poisontile.png", "", { PLAYER_WIDTH * 8, (MAP_HEIGHT / 2) + PLAYER_HEIGHT * 2, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    poison5 = new Entity(PLAYER_WIDTH * 7, (MAP_HEIGHT / 2) + PLAYER_HEIGHT * 3, 0, 0, 0, 0, 0, 0, "poisontile.png", "", { PLAYER_WIDTH * 7, (MAP_HEIGHT / 2) + PLAYER_HEIGHT * 3, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    forest2 = new Entity(PLAYER_WIDTH * 8, PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "foresttile.png", "", { PLAYER_WIDTH * 8, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::forest);
    forest3 = new Entity(PLAYER_WIDTH * 11, 0, 0, 0, 0, 0, 0, 0, "foresttile.png", "", { PLAYER_WIDTH * 11, 0, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::forest);
    boulder = new Entity(PLAYER_WIDTH * 5, (MAP_HEIGHT/2)+PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "boulder.png", "", { PLAYER_WIDTH * 5, (MAP_HEIGHT / 2) + PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::boulder);
    poison7 = new Entity(PLAYER_WIDTH * 5, (MAP_HEIGHT/2)-PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "poisontile.png", "", { PLAYER_WIDTH * 5, (MAP_HEIGHT / 2) - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    poison8 = new Entity(PLAYER_WIDTH * 4, MAP_HEIGHT/2, 0, 0, 0, 0, 0, 0, "poisontile.png", "", { PLAYER_WIDTH * 4, MAP_HEIGHT / 2, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    weapon = new Entity(PLAYER_WIDTH*5, MAP_HEIGHT/2, 0, 0, 0, 0, 0, 0, "sharpstick.png", "", { PLAYER_WIDTH * 5, MAP_HEIGHT / 2, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::tile);


    escape = new Entity(WINDOW_WIDTH - PLAYER_WIDTH, 0, 0, 0, 0, 0, 0, 0, "escapetile.png", "", { WINDOW_WIDTH - PLAYER_WIDTH, 0, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::escape);


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
    check = 0;
    pickup = false;

    for (int i = 0; i < entities.size(); ++i) {
        if (entities[i] == nullptr) {
            success = false;
        }
    }

    return success;
}

bool LevelThreeState::exit()
{
    for (int i = 0; i < entities.size(); ++i) {
        delete entities[i];
    }
    std::vector<Entity*>().swap(entities);
    return true;
}

void LevelThreeState::eventHandling(SDLWindow window, Game* manager)
{ 
    SDL_PumpEvents();
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
        if (player->getMove() <= 0) {
            player->setTurn(0);
        }
        if (e.type == SDL_EVENT_MOUSE_MOTION) {
            for (int i = 0; i < entities.size(); ++i) {
                if (entities[i]->mouseCheck()) {
                    entities[i]->mouseHandling(window);
                }
            }
        }
        if ((e.type == SDL_EVENT_KEY_DOWN) && (e.key.key == SDLK_RETURN))
        {
            std::string status;
            if (player->getAsset() == "celestriabloody.png") {
                status = "...";
            }
            else {
                if (player->getHealth() == 35) {
                    status = "I can do this!!";
                }
                else if (player->getHealth() <= 17) {
                    status = "I can do this.";

                }
                else if (player->getHealth() <= 5) {
                    status = "It's cold...";
                }
            }
            player->dialogue(window, status, 0, 20);

        }
        if (player->collisionCheck(player->getBounds(), weapon->getBounds()) && !pickup) {
            entities.erase(entities.end() - 2);
            player->setStrength(player->getStrength() + 15);
            window.boxRender("YOU'VE FOUND A WEAPON! ATK UP!");
            enemy1->setMove(6);
            MIX_StopAllTracks(window.mixer, 0);
            loop = SDL_CreateProperties();
            SDL_SetNumberProperty(loop, MIX_PROP_PLAY_LOOPS_NUMBER, -1);
            MIX_PlayTrack(bgm, loop);
            SDL_DestroyProperties(loop);
            SDL_RenderPresent(window.renderer);
            SDL_Delay(2000);
            pickup = true;
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
            if (player->collisionCheck(player->getBounds(), escape->getBounds())) {
                MIX_StopAllTracks(window.mixer, 0);
                manager->ChangeState(GameWinState::Instance());
            }
            player->playerInput(e, entities);
            if (e.key.key == SDLK_UP || e.key.key == SDLK_DOWN || e.key.key == SDLK_LEFT || e.key.key == SDLK_RIGHT) {
                MIX_PlayTrack(movesfx, 0);
            }

        }
        if ((e.type == SDL_EVENT_KEY_DOWN) && (e.key.key == SDLK_SPACE))
        {
            window.boxRender("ENDING TURN EARLY...");
            SDL_RenderPresent(window.renderer);
            SDL_Delay(500);
            player->setMove(0);
            player->setTurn(0);

        }
        if (e.type == SDL_EVENT_QUIT || e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) {
            manager->ChangeState(ExitState::Instance());
        }
    }
}

void LevelThreeState::update(Game* manager, SDLWindow window)
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
            MIX_StopAllTracks(window.mixer, 0);
            manager->ChangeState(GameWinState::Instance());
        }
        for (int i = 0; i < entities.size(); ++i) {
            if (entities[i]->getType() == ObjectType::forest && (player->collisionCheck(player->getBounds(), entities[i]->getBounds()))) {
                player->setAvoid(80);
            }
        }
        if (player->getEntityTurn() == 0) {
            if (player->collisionCheck(player->getBounds(), escape->getBounds())) {
                MIX_StopAllTracks(window.mixer, 0);
                manager->ChangeState(GameWinState::Instance());
            }
            //enemyturn
            player->setTurn(0);
            int size;
            if (player->getAsset() == "celestriabloody.png") {
                size = entities.size() - 2;
            }
            else {
                size = entities.size() - 1;
            }
            for (int i = 1; i < size; ++i) {
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
                        MIX_PlayTrack(damagesfx, 0);
                        SDL_RenderPresent(window.renderer);
                        SDL_Delay(2000);
                    }

                    if (entities[i]->getHealth() < temp2) {
                        int diff2 = temp2 - entities[i]->getHealth();
                        window.boxRender("PLAYER MANAGES TO DEAL " + std::to_string(diff2) + " TO Enemy " + std::to_string(i) + "!");
                        MIX_PlayTrack(damagesfx, 0);
                        SDL_RenderPresent(window.renderer);
                        window.boxRender("PLAYER MANAGES TO DEAL " + std::to_string(diff2) + " TO Enemy " + std::to_string(i) + "!");
                        SDL_RenderPresent(window.renderer);
                        SDL_Delay(2000);
                        if (entities[i]->getHealth() <= 0) {
                            window.boxRender("PLAYER MANAGES TO KILL Enemy " + std::to_string(i) + "!");
                            SDL_RenderPresent(window.renderer);
                            entities.erase(entities.begin() + i);
                            MIX_StopAllTracks(window.mixer, 0);
                            player->setAsset("celestriabloody.png");
                            window.boxRender("PLAYER MANAGES TO KILL Enemy " + std::to_string(i) + "!");
                            SDL_RenderPresent(window.renderer);
                            MIX_PlayTrack(killsfx, 0);
                            SDL_Delay(2500);
                        }
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
                if (player->collisionCheck(player->getBounds(), escape->getBounds())) {
                    MIX_StopAllTracks(window.mixer, 0);
                    manager->ChangeState(GameWinState::Instance());
                }
                player->setMove(2);
                SDL_RenderPresent(window.renderer);
                SDL_Delay(1000);
                player->setAvoid(20);
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
    else {
        window.boxRender("ENEMY TURN");
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

        std::string musicPath = "assets//mus//bgm//battle.mp3";
        MIX_Audio* mus = MIX_LoadAudio(window.mixer, musicPath.c_str(), false);
        bgm = MIX_CreateTrack(window.mixer);
        MIX_SetTrackAudio(bgm, mus);

        std::string sfx2Path = "assets//mus//sfx//damage.mp3";
        MIX_Audio* sfx2 = MIX_LoadAudio(window.mixer, sfx2Path.c_str(), false);
        damagesfx = MIX_CreateTrack(window.mixer);
        MIX_SetTrackAudio(damagesfx, sfx2);

        std::string sfx3Path = "assets//mus//sfx//kill.mp3";
        MIX_Audio* sfx3 = MIX_LoadAudio(window.mixer, sfx3Path.c_str(), false);
        killsfx = MIX_CreateTrack(window.mixer);
        MIX_SetTrackAudio(killsfx, sfx3);
        SDL_Delay(2000);
        check += 1;
    }
}




