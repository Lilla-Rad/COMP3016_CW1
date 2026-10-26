#include "Entity.h"
#include "SDLWindow.h"
#include <iostream>

void Entity::render(SDLWindow window) {
	SDL_FRect objRect = { getX(), getY(), PLAYER_WIDTH, PLAYER_HEIGHT };
	window.renderTextureFromFile(getAsset(), NULL, &objRect);

}

void Entity::MoveUp() {
	if (y > 0)
		y -= PLAYER_HEIGHT;
	this->setBounds({ this->getBounds().x, y, this->getBounds().h, this->getBounds().w });
	move -= 1;
}

void Entity::MoveDown() {
	if (y + PLAYER_HEIGHT < BASE_HEIGHT - BOX_HEIGHT)
		y += PLAYER_HEIGHT;
	this->setBounds({ this->getBounds().x, y, this->getBounds().h, this->getBounds().w });
	move -= 1;
}

void Entity::MoveLeft() {
	if (x > 0)
		x -= PLAYER_WIDTH;
	this->setBounds({ x, this->getBounds().y, this->getBounds().h, this->getBounds().w });
	move -= 1;
}

void Entity::MoveRight() {
	if (x + PLAYER_WIDTH < BASE_WIDTH)
		x += PLAYER_WIDTH;
	this->setBounds({ x, this->getBounds().y, this->getBounds().h, this->getBounds().w });
	move -= 1;
}

void Entity::Die() {
	if (getHealth() <= 0) {

	}
}

void Entity::playerInput(SDL_Event& e) {
	if (getEntityTurn() == 1) {
		const bool* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_UP] && !(state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_LEFT])) {
			setSpeed(5);
			MoveUp();


		}
		if (state[SDL_SCANCODE_DOWN] && !(state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_LEFT])) {
			setSpeed(5);
			MoveDown();
		}
		if (state[SDL_SCANCODE_RIGHT] && !(state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN])) {
			setSpeed(5);
			MoveRight();
		}
		if (state[SDL_SCANCODE_LEFT] && !(state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN])) {
			setSpeed(5);
			MoveLeft();
		}
		if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_DOWN]) {
			setSpeed(0);
		}
	}
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