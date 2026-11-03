#include "GameWinState.h"
#include <iostream>
#include "Constants.h"
#include "SDLWindow.h"
#include "ExitState.h"



GameWinState GameWinState::stateGameWin;

bool GameWinState::enter()
{
    bool success = true;

    player = new Entity(WINDOW_WIDTH/2, 0, 5, 1, 20, 10, 10, 4, "whatsss.png", "rvoice.mp3", { WINDOW_WIDTH / 2,0, PLAYER_WIDTH, PLAYER_HEIGHT }, ObjectType::player);
    MIX_Mixer* mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    std::string musicPath = "assets//mus//bgm//gamewin.mp3";
    MIX_Audio* bgm = MIX_LoadAudio(mixer, musicPath.c_str(), false);
    track = MIX_CreateTrack(mixer);
    MIX_SetTrackAudio(track, bgm);
    MIX_PlayTrack(track, 0);

    return success;
}

bool GameWinState::exit()
{
    return true;
}

void GameWinState::eventHandling(SDLWindow window, Game* manager)
{
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_QUIT || e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) {
            manager->ChangeState(ExitState::Instance());
        }
    }
}


void GameWinState::update(Game* manager, SDLWindow window)
{

}


void GameWinState::Render(SDLWindow window)
{
    
    SDL_RenderClear(window.renderer);
    SDL_FRect windowRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    window.renderTextureFromFile("placeholderwin.jpg", NULL, &windowRect);
    SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_SetRenderScale(window.renderer, SCALAR * 3, SCALAR * 3);
    SDL_RenderDebugText(window.renderer, WINDOW_WIDTH / 10, WINDOW_HEIGHT / 7, "YOU ESCAPED");
    SDL_SetRenderScale(window.renderer, SCALAR, SCALAR);
    SDL_RenderDebugText(window.renderer, WINDOW_WIDTH/2- (PLAYER_WIDTH*3)-(PLAYER_WIDTH/4), (MAP_HEIGHT / 2) + PLAYER_HEIGHT, "You ran until they couldn't.");
    SDL_RenderPresent(window.renderer);

}