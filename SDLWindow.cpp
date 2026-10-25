#include "SDLWindow.h"
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "Constants.h"

bool SDLWindow::Init() {
	bool success{ true };
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == false) {
		SDL_Log("SDL failed to initialise! SDL error: %s\n", SDL_GetError());
		//success = false;
	}
	if (SDL_CreateWindowAndRenderer("test", WINDOW_WIDTH, WINDOW_HEIGHT, NULL, &window, &renderer) == false) {
		SDL_Log("Could not create window! SDL error: %s\n", SDL_GetError());
	}
	else {
		if (MIX_Init() == false) {
			SDL_Log("Could not initialise mixer! SDL_mixer error: %s\n", SDL_GetError());
			//success = false;
		}
		else {
			if (mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr); mixer == nullptr) {
				SDL_Log("SDL_mixer failed to create mixer! SDL_mixer error: %s\n", SDL_GetError());
				//success = false;
			}
		}
	}
	return success;

}

SDLWindow::SDLWindow() {
	Init();
	SDL_FRect boxRect = { 0, MAP_HEIGHT / SCALAR, WINDOW_WIDTH / SCALAR, WINDOW_HEIGHT / SCALAR };
	renderTextureFromFile("adachi-rei-machina-mori.png", NULL, &boxRect);
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



/*SDLWindow::~SDLWindow()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
	MIX_DestroyMixer(mixer);
	SDL_Quit();
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