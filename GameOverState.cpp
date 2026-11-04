#include "GameOverState.h"
#include <iostream>
#include "Constants.h"
#include "SDLWindow.h"
#include "ExitState.h"
#include <SDL3_mixer/SDL_mixer.h>


GameOverState GameOverState::stateGameOver;

bool GameOverState::enter()
{
    bool success = true;
    MIX_Mixer* mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    std::string musicPath = "assets//mus//bgm//gameover.mp3";
    MIX_Audio* bgm = MIX_LoadAudio(mixer, musicPath.c_str(), false);
    track = MIX_CreateTrack(mixer);
    MIX_SetTrackAudio(track, bgm);
    loop = SDL_CreateProperties();
    SDL_SetNumberProperty(loop, MIX_PROP_PLAY_LOOPS_NUMBER, -1);
    MIX_PlayTrack(track, loop);
    SDL_DestroyProperties(loop);
    
    return success;
}

bool GameOverState::exit()
{
    return true;
}

void GameOverState::eventHandling(SDLWindow window, Game* manager)
{
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_QUIT || e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) {
            manager->ChangeState(ExitState::Instance());
        }
    }
}

void GameOverState::update(Game* manager, SDLWindow window)
{

}


void GameOverState::Render(SDLWindow window)
{
    SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(window.renderer);
    SDL_SetRenderDrawColor(window.renderer, 255, 255, 255, 255);
    SDL_SetRenderScale(window.renderer, SCALAR * 3, SCALAR * 3);
    SDL_RenderDebugText(window.renderer, WINDOW_WIDTH/10, WINDOW_HEIGHT/7, "GAME OVER");
    SDL_SetRenderScale(window.renderer, SCALAR, SCALAR);
    SDL_RenderPresent(window.renderer);


}