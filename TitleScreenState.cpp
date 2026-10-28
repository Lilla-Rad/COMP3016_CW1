#include "TitleScreenState.h"
#include <iostream>
#include "Constants.h"
#include "SDLWindow.h"
#include "LevelOneState.h"
#include "ExitState.h"
#include <SDL3_mixer/SDL_mixer.h>


TitleScreenState TitleScreenState::stateTitleScreen;

bool TitleScreenState::enter()
{
    bool success = true;
    MIX_Mixer* mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);

    std::string musicPath = "assets//mus//bgm//placeholdertitle.mp3";
    MIX_Audio* bgm = MIX_LoadAudio(mixer, musicPath.c_str(), false);
    MIX_Track* title = MIX_CreateTrack(mixer);
    MIX_SetTrackAudio(title, bgm);
    MIX_PlayTrack(title, 0);


    return success;
}

bool TitleScreenState::exit()
{
    MIX_StopAllTracks(mixer, 0);
    MIX_DestroyTrack(title);
    MIX_DestroyMixer(mixer);
    return true;
}

void TitleScreenState::eventHandling(SDLWindow window, Game* manager)
{
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_SPACE) {
            MIX_StopAllTracks(mixer, 0);
            MIX_StopTrack(title, 0);
            MIX_DestroyTrack(title);
            MIX_DestroyMixer(mixer);
            exit();
            manager->ChangeState(LevelOneState::Instance());
        }
        if (e.type == SDL_EVENT_QUIT || e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) {
            manager->ChangeState(ExitState::Instance());
        }
    }
}


void TitleScreenState::update(Game* manager)
{

}


void TitleScreenState::Render(SDLWindow window)
{

    SDL_RenderClear(window.renderer);
    SDL_FRect windowRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    window.renderTextureFromFile("temptitle.png", NULL, &windowRect);
    SDL_SetRenderDrawColor(window.renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_SetRenderScale(window.renderer, SCALAR*2, SCALAR*2);
    SDL_RenderDebugText(window.renderer, PLAYER_WIDTH, MAP_HEIGHT / 5, GAME_TITLE.c_str());
    SDL_SetRenderScale(window.renderer, SCALAR, SCALAR);
    SDL_RenderDebugText(window.renderer, PLAYER_WIDTH*2, MAP_HEIGHT / 2, "PRESS SPACE TO BEGIN");
    SDL_RenderPresent(window.renderer);


}