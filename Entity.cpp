#include "Entity.h"
#include "SDLWindow.h"

void Entity::render(SDLWindow window) {
	SDL_FRect objRect = { getX(), getY(), PLAYER_WIDTH, PLAYER_HEIGHT };
	window.renderTextureFromFile(getAsset(), NULL, &objRect);

}

void Entity::dialogue(SDLWindow window, std::string speech, bool pos, int delay) {
	std::string path = "assets//mus//sfx//" + getVoice();
	std::string empty = "";
	float xpos;
	float ypos;
	float len = speech.length();
	MIX_Mixer* mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
	MIX_Audio* talk = MIX_LoadAudio(mixer, path.c_str(), false);
	MIX_Track* track = MIX_CreateTrack(mixer);
	MIX_SetTrackAudio(track, talk);
	SDL_SetRenderScale(window.renderer, SCALAR, SCALAR);
	SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
	if ((getX() + PLAYER_WIDTH) / SCALAR >= WINDOW_WIDTH / SCALAR || (getX() + ((len / 2) * 8)) / SCALAR >= WINDOW_WIDTH / SCALAR) {
		xpos = WINDOW_WIDTH - (len * (8 * SCALAR));
	}
	else if (getX() / SCALAR == 0 || (getX() - ((len / 2) * 8) + PLAYER_WIDTH) / SCALAR < 0) {
		xpos = 0;
	}
	else {
		xpos = getX() - ((len / 2) * 8) + (PLAYER_WIDTH / 2);
	}
	if (getY() == 0 || pos) {
		ypos = getY() + PLAYER_HEIGHT;
	}
	else {
		ypos = getY() - PLAYER_HEIGHT / 2;
	}
	if (!(0 <= xpos <= WINDOW_WIDTH) || !(0 <= ypos <= WINDOW_HEIGHT)) {
		MIX_Track* trackb = MIX_CreateTrack(mixer);
		MIX_Audio* kys = MIX_LoadAudio(mixer, "assets//mus//sfx//ppop-online-audio-converter.mp3", false);
		MIX_SetTrackAudio(trackb, kys);
		MIX_PlayTrack(trackb, 0);
		xpos = 0 + (WINDOW_WIDTH / 7.0);
		ypos = 0 + ((WINDOW_HEIGHT / 1.6) - (8 * len));

	}
	for (int i = 0; i < len; ++i) {
		empty += speech[i];
		SDL_RenderDebugText(window.renderer, xpos, ypos, empty.c_str());
		SDL_Delay(50);
		SDL_RenderPresent(window.renderer);
		MIX_PlayTrack(track, 0);
		SDL_Delay(delay);
	}
	SDL_RenderDebugText(window.renderer, xpos, ypos, speech.c_str());

	SDL_RenderPresent(window.renderer);
	SDL_SetRenderScale(window.renderer, SCALAR, SCALAR);
	SDL_Delay(1000);
}