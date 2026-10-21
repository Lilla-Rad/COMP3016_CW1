#include "Object.h"
#include <SDL3_mixer/SDL_mixer.h>
#include <iostream>

bool Object::collisionCheck(SDL_Rect a, SDL_Rect b) {
	int minxA{ a.x };
	int maxxA{ a.x + a.w };
	int minyA{ a.y };
	int maxyA{ a.y + a.h };

	int minxB{ b.x };
	int maxxB{ b.x + b.w };
	int minyB{ b.y };
	int maxyB{ b.y + b.h };

	if (minxA == minxB && maxxA == maxxB && minyA == minyB && maxyA == maxyB) {
		return false;
	}

	if (minxA >= maxxB) {
		return false;
	}

	if (maxxA <= minxB) {
		return false;
	}

	if (minyA >= maxyB) {
		return false;
	}

	if (maxyA <= minyB) {
		return false;
	}

	return true;

}


void Object::handleCollision(Object* objectA, Object* objectB) {
	if (objectA->getType() == ObjectType::player && objectB->getType() == ObjectType::enemy) {
		SDL_Init(SDL_INIT_AUDIO);
		MIX_Mixer* mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
		std::string musicPath = "u_xg7ssi08yr-comical-kiss-2-381978.mp3";
		MIX_Audio* kissy = MIX_LoadAudio(mixer, "u_xg7ssi08yr-comical-kiss-2-381978.mp3", false);
		MIX_Track* track = MIX_CreateTrack(mixer);
		MIX_SetTrackAudio(track, kissy);
		MIX_PlayTrack(track, 0);
		std::cout << "riddlebird kiss <3";
	}
}