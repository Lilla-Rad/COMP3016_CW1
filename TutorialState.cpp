#include "TutorialState.h"
#include "ExitState.h"
#include "LevelOneState.h"
#include <iostream>


TutorialState TutorialState::stateTutorial;

bool TutorialState::enter()
{
    bool success = true;

    player = new Entity(WINDOW_WIDTH / 2, 0, 5, 1, 20, 10, 10, 4, "celestriasprite.png", "testvoice.mp3", { WINDOW_WIDTH / 2, 0, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::player);
    forest1 = new Entity(WINDOW_WIDTH - (PLAYER_WIDTH * 2), MAP_HEIGHT - PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "foresttile.png", "", { WINDOW_WIDTH - (PLAYER_WIDTH * 2), MAP_HEIGHT - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::forest);
    forest2 = new Entity(PLAYER_WIDTH * 4, PLAYER_HEIGHT * 3, 0, 0, 0, 0, 0, 0, "foresttile.png", "", { PLAYER_WIDTH * 4, PLAYER_HEIGHT * 3, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::forest);
    forest3 = new Entity(WINDOW_WIDTH - (PLAYER_WIDTH * 4), PLAYER_HEIGHT * 3, 0, 0, 0, 0, 0, 0, "foresttile.png", "", { WINDOW_WIDTH - (PLAYER_WIDTH * 4), PLAYER_HEIGHT * 3, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::forest);
    enemy1 = new Entity(0, MAP_HEIGHT / 2, 5, 0, 20, 20, 20 * DIFFICULTY, 6, "soldiersprite.png", "testvoice2.mp3", { 0, MAP_HEIGHT / 2, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::enemy);
    enemy2 = new Entity(PLAYER_WIDTH * 3, MAP_HEIGHT - PLAYER_HEIGHT, 5, 0, 20, 20, 20 * DIFFICULTY, 6, "soldiersprite.png", "testvoice2.mp3", { PLAYER_WIDTH * 3, MAP_HEIGHT - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::enemy);
    boulder = new Entity(WINDOW_WIDTH - PLAYER_WIDTH, MAP_HEIGHT - (PLAYER_HEIGHT * 2), 0, 0, 0, 0, 0, 0, "boulder.png", "", { WINDOW_WIDTH - PLAYER_WIDTH, MAP_HEIGHT - PLAYER_HEIGHT * 2, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::boulder);

    poison1 = new Entity(WINDOW_WIDTH - (PLAYER_WIDTH * 3), MAP_HEIGHT - PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "poisontile.png", "", { WINDOW_WIDTH - (PLAYER_WIDTH * 3), MAP_HEIGHT - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);
    poison2 = new Entity(WINDOW_WIDTH - (PLAYER_WIDTH * 2), MAP_HEIGHT - (PLAYER_HEIGHT * 2), 0, 0, 0, 0, 0, 0, "poisontile.png", "", { WINDOW_WIDTH - (PLAYER_WIDTH * 2), MAP_HEIGHT - (PLAYER_HEIGHT * 2), PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::poison);

    escape = new Entity(WINDOW_WIDTH - PLAYER_WIDTH, MAP_HEIGHT - PLAYER_HEIGHT, 0, 0, 0, 0, 0, 0, "escapetile.png", "", { WINDOW_WIDTH - PLAYER_WIDTH, MAP_HEIGHT - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::escape);

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
    int tutorial = 0;
    
    for (int i = 0; i < entities.size(); ++i) {
        if (entities[i] == nullptr) {
            success = false;
        }
    }

    return success;
}

bool TutorialState::exit()
{
    for (int i = 0; i < entities.size(); ++i) {
        delete entities[i];
    }
    std::vector<Entity*>().swap(entities);
    return true;
}



void TutorialState::eventHandling(SDLWindow window, Game* manager)
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_QUIT || e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) {
            manager->ChangeState(ExitState::Instance());
        }
        else if (e.type == SDL_EVENT_KEY_DOWN && tutorial >= 10) {
            manager->ChangeState(LevelOneState::Instance());
        }

    }

}


void TutorialState::update(Game* manager, SDLWindow window)
{
    if (tutorial == 0) {
        std::string sfxPath = "assets//mus//sfx//move.mp3";
        MIX_Audio* sfx = MIX_LoadAudio(window.mixer, sfxPath.c_str(), false);
        movesfx = MIX_CreateTrack(window.mixer);
        MIX_SetTrackAudio(movesfx, sfx);
    }
}



void TutorialState::Render(SDLWindow window)
{
    SDL_RenderClear(window.renderer);
    SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
    SDL_FRect mapRect = { 0, 0, WINDOW_WIDTH, MAP_HEIGHT };
    window.renderTextureFromFile("dirtmap.png", NULL, &mapRect);
    SDL_FRect boxRect = { 0, MAP_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT };
    if (tutorial >= 10) {
        window.boxRender("Move with < \u005e > v");
    }
    else {
        window.boxRender("");
    }

    //render in reverse order to render player on top of terrain
    if (tutorial > 9) {
        for (int i = entities.size() - 1; i >= 0; --i) {
            entities[i]->render(window);
        }

    }
    else if (tutorial > 5) {
        for (int i = entities.size() - 2; i >= 0; --i) {
            entities[i]->render(window);
        }

    }
    else {
        player->render(window);
    }


    SDL_RenderPresent(window.renderer);

    switch (tutorial) {
    case 0: 
        tutorial += 1;
        break;
    case 1:
        player->dialogue(window, "Please, just leave me alone!", 0, 30);
        tutorial += 1;
        break;
    case 4:
        tutorial += 1;
        break;
    case 5:
        player->dialogue(window, "Phew... did I lose them?", 0, 50);
        SDL_Delay(500);
        tutorial += 1;
        break;
    case 6:
        tutorial += 1;
        break;
    case 7:
        enemy1->dialogue(window, "STOP RIGHT THERE!", 0, 50);
        enemy2->dialogue(window, "Get back here!!", 0, 50);
        player->dialogue(window, "EEP!", 0, 30);
        tutorial += 1;
        break;
    case 8:
        tutorial += 1;
        break;
    case 9:
        escape->render(window);
        SDL_Delay(500);
        player->dialogue(window, "If I make it there, I should be safe...", 0, 50);
        tutorial += 1;
        break;
    }

    if (tutorial > 1 && tutorial < 4) {
        player->render(window);
        player->MoveDown(entities, 0);
        MIX_PlayTrack(movesfx, 0);
        SDL_Delay(500);
        tutorial += 1;
    }

}