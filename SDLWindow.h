#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>

class SDLWindow
{
public:
	SDLWindow();
	bool Init();
	void Quit();
	bool renderTextureFromFile(std::string path, const SDL_FRect* srcrect, const SDL_FRect* dstrect);
	void boxRender(std::string info);
	void cleanup(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture, MIX_Mixer* mixer);
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	MIX_Mixer* mixer;
	SDL_PropertiesID options;

};

