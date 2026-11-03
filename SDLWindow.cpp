#include "SDLWindow.h"
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "Constants.h"
#include <iostream>

bool SDLWindow::Init() {
	bool success{ true };
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == false) {
		SDL_Log("SDL failed to initialise! SDL error: %s\n", SDL_GetError());
		success = false;
	}
	if (SDL_CreateWindowAndRenderer(GAME_TITLE.c_str(), WINDOW_WIDTH, WINDOW_HEIGHT, NULL, &window, &renderer) == false) {
		SDL_Log("Could not create window! SDL error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		SDL_Surface* iconSur = IMG_Load(WINDOW_ICON.c_str());
		if (!iconSur) {
			SDL_Log("Could not load window icon surface! SDL error: %s\n", SDL_GetError());
			success = false;
		}
		if (!SDL_SetWindowIcon(this->window, iconSur)) {
			SDL_Log("Could not set window icon! SDL error: %s\n", SDL_GetError());
			success = false;
		}
		if (MIX_Init() == false) {
			SDL_Log("Could not initialise mixer! SDL_mixer error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			if (mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr); mixer == nullptr) {
				SDL_Log("SDL_mixer failed to create mixer! SDL_mixer error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				std::string musicPath = "assets//mus//bgm//placeholdertitle.mp3";
				if (MIX_Audio* bgm = MIX_LoadAudio(mixer, musicPath.c_str(), false); bgm == nullptr) {
					SDL_Log("SDL_mixer failed to load title track! SDL_mixer error: %s\n", SDL_GetError());
				}
				else {
					if (MIX_Track* title = MIX_CreateTrack(mixer); title == nullptr) {
						SDL_Log("SDL_mixer failed to create title track! SDL_mixer error: %s\n", SDL_GetError());
					}
					else {
						MIX_SetTrackAudio(title, bgm);
						MIX_PlayTrack(title, 0);
					}
				}
			}
			

		}
	}
	return success;

}

SDLWindow::SDLWindow() {
	if (!Init()) {
		cleanup(window, renderer, texture, mixer);
	}
}

bool SDLWindow::renderTextureFromFile(std::string path, const SDL_FRect* srcrect, const SDL_FRect* dstrect) {
	SDL_DestroyTexture(texture);
	texture = nullptr;
	path = "assets\\img\\" + path;
	if (SDL_Surface* loadedSurface = IMG_Load(path.c_str()); loadedSurface == nullptr) {
		SDL_Log("Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError());
	}
	else {
		if (texture = SDL_CreateTextureFromSurface(renderer, loadedSurface); texture == nullptr) {
			SDL_Log("Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError());
		}
		else {
			SDL_RenderTexture(renderer, texture, srcrect, dstrect);
		}

		SDL_DestroySurface(loadedSurface);
	}
	return texture != nullptr;
}

void SDLWindow::boxRender(std::string info) {
	SDL_FRect boxRect = { 0, MAP_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT };
	renderTextureFromFile(BOX_TEXTURE, NULL, &boxRect);
	SDL_SetRenderScale(renderer, SCALAR * 2, SCALAR * 2);
	SDL_RenderDebugText(renderer, (WINDOW_WIDTH * 0.0125) / (SCALAR * 2), (WINDOW_HEIGHT - BOX_HEIGHT) / (SCALAR * 2) + (BOX_HEIGHT / 3) / (SCALAR * 2), info.c_str());
	SDL_SetRenderScale(renderer, SCALAR, SCALAR);
}


/*SDLWindow::~SDLWindow()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
	//MIX_DestroyMixer(mixer);
	exit(1);
}*/

void SDLWindow::Clear() {
	SDL_RenderClear(renderer);
}

void SDLWindow::Present() {
	SDL_RenderPresent(renderer);
}

void SDLWindow::cleanup(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture, MIX_Mixer* mixer) {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
	MIX_DestroyMixer(mixer);
}

void SDLWindow::Quit() {
	SDL_Quit();
}