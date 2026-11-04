#include "Entity.h"
#include "SDLWindow.h"
#include <iostream>
#include <vector>
#include <random>

void Entity::render(SDLWindow window) {
	SDL_FRect objRect = { getX(), getY(), PLAYER_WIDTH, PLAYER_HEIGHT };
	window.renderTextureFromFile(getAsset(), NULL, &objRect);

}

bool Entity::collisionCheck(SDL_Rect a, SDL_Rect b) {
	int minxA{ a.x };
	int maxxA{ a.x + a.w };
	int minyA{ a.y };
	int maxyA{ a.y + a.h };

	int minxB{ b.x };
	int maxxB{ b.x + b.w };
	int minyB{ b.y };
	int maxyB{ b.y + b.h };

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

void Entity::mouseHandling(SDLWindow window) {
	//DL_FRect movemapRect;
	int x = getX() - (PLAYER_WIDTH * getMove());
	int y = getY() - (PLAYER_HEIGHT * getMove());
	int width = (2 * (PLAYER_WIDTH * getMove())) + PLAYER_WIDTH;
	int height = 2 * (PLAYER_HEIGHT * getMove()) + PLAYER_HEIGHT;
	SDL_FRect movemapRect = { x, y, width, height };
	switch (getType()) {
	case ObjectType::player:
		switch (getMove()) {
		case 1:
			window.renderTextureFromFile("playermove1.png", NULL, &movemapRect);
			break;
		case 2:
			window.renderTextureFromFile("playermove2.png", NULL, &movemapRect);
			break;
		case 3:
			window.renderTextureFromFile("playermove3.png", NULL, &movemapRect);
			break;
		case 4:
			window.renderTextureFromFile("playermove4.png", NULL, &movemapRect);
			break;
		}
		window.boxRender("Current health: " + std::to_string(getHealth()) + " | Atk:" + std::to_string(getStrength()));
		break;
	case ObjectType::enemy:
		switch (getMove()) {
		case 1:
			window.renderTextureFromFile("enemymove1.png", NULL, &movemapRect);
			break;
		case 2:
			window.renderTextureFromFile("enemymove2.png", NULL, &movemapRect);
			break;
		case 3:
			window.renderTextureFromFile("enemymove3.png", NULL, &movemapRect);
			break;
		case 4:
			window.renderTextureFromFile("enemymove4.png", NULL, &movemapRect);
			break;
		}
		switch (getStrength()) {
		case 30:
			window.boxRender("Knight | Health:" + std::to_string(getHealth()) + " | Atk:" + std::to_string(getStrength()) + " | Move:" + std::to_string(getMove()));
			break;
		case 40:
			window.boxRender("Paladin | Health:" + std::to_string(getHealth()) + " | Atk:" + std::to_string(getStrength()) + " | Move:" + std::to_string(getMove()));
			break;
		default:
			window.boxRender("Soldier | Health:" + std::to_string(getHealth()) + " | Atk:" + std::to_string(getStrength()) + " | Move:" + std::to_string(getMove()));
		}
		break;
	case ObjectType::forest:
		window.boxRender("Forest tile (+60 Avoid)");
		break;
	case ObjectType::boulder:
		window.boxRender("Boulder");
		break;
	case ObjectType::escape:
		window.boxRender("Escape tile");
		break;
	case ObjectType::poison:
		window.boxRender("Poison tile");
		break;
	case ObjectType::tile:
		window.boxRender("Sharp stick (+15 Atk)");
		break;
	default:
		window.boxRender("Entity");
	}
	SDL_RenderPresent(window.renderer);
	SDL_Delay(3000);
}

void Entity::takeTurn(std::vector<Entity*> entities, int position) {
	if (getEntityTurn() == 1) {
		for (int m = 0; m <= getMove(); ++m) {
			int currentX = getX();
			int currentY = getY();
			int targetX = entities[0]->getX();
			int targetY = entities[0]->getY();
			//if enemy is right next to player, 25% chance they might move elsewhere (failsafe against boxing the player in)
			if (targetX == currentX - PLAYER_WIDTH || targetX == currentX + PLAYER_WIDTH || targetY == currentY - PLAYER_HEIGHT || targetY == currentY + PLAYER_HEIGHT) {
				std::random_device seed;
				std::mt19937 gen{ seed() };
				std::uniform_int_distribution<> dist{ 1, 16 };
				int move = dist(gen);
				switch (move) {
				case 1:
					MoveLeft(entities, position);
					break;
				case 2:
					MoveUp(entities, position);
					break;
				case 3:
					MoveRight(entities, position);
					break;
				case 4:
					MoveDown(entities, position);
					break;
				default:
					//if enemy is to player's right
					if (targetX < currentX) {
						MoveLeft(entities, position);
					}
					//if enemy is to player's left
					if (targetX > currentX) {
						MoveRight(entities, position);
					}
					//if enemy is above player
					if (targetY > currentY) {
						MoveDown(entities, position);
					}
					//if enemy is below player
					if (targetY < currentY) {
						MoveUp(entities, position);
					}
				}
			}
			else {

				//if enemy is to player's right
				if (targetX < currentX) {
					MoveLeft(entities, position);
				}
				//if enemy is to player's left
				if (targetX > currentX) {
					MoveRight(entities, position);
				}
				//if enemy is above player
				if (targetY > currentY) {
					MoveDown(entities, position);
				}
				//if enemy is below player
				if (targetY < currentY) {
					MoveUp(entities, position);
				}
			}

		}
		setTurn(0);
	}
	switch (getStrength()) {
		case 30:
			setMove(3);
			break;
		case 40:
			setMove(2);
			break;
		default:
			setMove(4);
	}
	
}

void Entity::combat(Entity* victim) {
	std::random_device seed;
	std::mt19937 gen{ seed() };
	int maxDamage;
	maxDamage = (getStrength() * (100 - (victim->getAvoid()))) / 100;
	std::uniform_int_distribution<> dist1{ 1, maxDamage };
	int dodgechance = victim->getAvoid();
	std::uniform_int_distribution<> dist2{ 0, dodgechance };
	int damage = dist1(gen);
	if (damage > victim->getHealth()) {
		damage = victim->getHealth();
	}
	int dodge = dist2(gen);
	if (victim->getAvoid() > 60) {
		damage = 0;
	}
	if (damage > dodge) {
		victim->setHealth(victim->getHealth() - damage);
	}
	if (victim->getStrength() >= 10) {
		setHealth(getHealth() - damage / 2);
	}
	setTurn(0);
}

void Entity::handleCollision(Entity* collided) {
	if (getType() == ObjectType::enemy && collided->getType() == ObjectType::player) {
		combat(collided);
	}
	else if (getType() == ObjectType::enemy && collided->getType() == ObjectType::poison) {
		setHealth(getHealth() - (getHealth() * 0.1));
	}
	else if (getType() == ObjectType::player && collided->getType() == ObjectType::enemy && getStrength() >= 10) {
		combat(collided);
	}
}


//check if there is anything adjacent, and if so return a value corresponding to the type of adjacent entity
//return the first adjacent entity, ignore anything else (e.g. if there are multiple adjacent units
int Entity::checkForCollidables(std::vector<Entity*> entities, int position, int direction) {
	bool collided = false;
	std::vector<Entity*> temp = entities;
	SDL_Rect backup = getBounds();
	if (position == 0) {
		temp.erase(temp.begin());
	}
	else {
		temp.erase(temp.begin() + position);
	}
	for (int i = 0; i < temp.size(); ++i) {
		if (temp[i]->getType() == ObjectType::boulder) {
			
			this->setBounds({ (this->getBounds().x) - PLAYER_WIDTH, this->getBounds().y,getBounds().h, getBounds().w });
			if (collisionCheck(getBounds(), temp[i]->getBounds())) {
				collided = true;
			}
			this->setBounds({ (this->getBounds().x) + (PLAYER_WIDTH*2), this->getBounds().y, this->getBounds().h, this->getBounds().w });
			if (collisionCheck(getBounds(), temp[i]->getBounds())) {
				collided = true;
			}
			this->setBounds({ (this->getBounds().x) - PLAYER_WIDTH, (this->getBounds().y) - PLAYER_HEIGHT, this->getBounds().h, this->getBounds().w });
			if (collisionCheck(getBounds(), temp[i]->getBounds())) {
				collided = true;
			}
			this->setBounds({ this->getBounds().x, (this->getBounds().y) + (PLAYER_HEIGHT*2), this->getBounds().h, this->getBounds().w });
			if (collisionCheck(getBounds(), temp[i]->getBounds())) {
				collided = true;
			}
			this->setBounds(backup);
			if (collided) {
				if (temp[i]->getType() == ObjectType::boulder) {
					if (direction == 1) {
						temp[i]->MoveLeft(entities, i + 1);
					}
					return 1;
				}
				break;
			}
			else {
				return 3;
			}
		}
	}
}


void Entity::MoveUp(std::vector<Entity*> entities, int position) {
	y -= PLAYER_HEIGHT;
	move -= 1;
	this->setBounds({ this->getBounds().x, y, this->getBounds().h, this->getBounds().w });
	std::vector<Entity*> temp = entities;
	temp.erase(temp.begin() + position);
	bool collided = false;
	for (int i = 0; i < temp.size(); ++i) {
		if (temp[i]->getType() == ObjectType::enemy || temp[i]->getType() == ObjectType::boulder || temp[i]->getType() == ObjectType::player) {
			collided = collisionCheck(getBounds(), temp[i]->getBounds());
		}
		if (collided == true) {
			handleCollision(temp[i]);
			break;
		}
	}

	if (y < 0 || collided) {
		y += PLAYER_HEIGHT;
		move += 1;
	}
	this->setBounds({ this->getBounds().x, y, this->getBounds().h, this->getBounds().w });
}

void Entity::MoveDown(std::vector<Entity*> entities, int position) {
	y += PLAYER_HEIGHT;
	move -= 1;
	this->setBounds({ this->getBounds().x, y, this->getBounds().h, this->getBounds().w });
	std::vector<Entity*> temp = entities;
	temp.erase(temp.begin() + position);
	bool collided = false;
	for (int i = 0; i < temp.size(); ++i) {
		if (temp[i]->getType() == ObjectType::enemy || temp[i]->getType() == ObjectType::boulder || temp[i]->getType() == ObjectType::player) {
			collided = collisionCheck(getBounds(), temp[i]->getBounds());
		}
		if (collided == true) {
			handleCollision(temp[i]);
			break;
		}
	}

	if (y + PLAYER_HEIGHT > BASE_HEIGHT - BOX_HEIGHT || collided) {
		y -= PLAYER_HEIGHT;
		move += 1;
	}
	this->setBounds({ this->getBounds().x, y, this->getBounds().h, this->getBounds().w });


}

void Entity::MoveLeft(std::vector<Entity*> entities, int position) {
	x -= PLAYER_WIDTH;
	move -= 1;
	this->setBounds({ x, this->getBounds().y, this->getBounds().h, this->getBounds().w });
	std::vector<Entity*> temp = entities;
	temp.erase(temp.begin() + position);
	bool collided = false;
	for (int i = 0; i < temp.size(); ++i) {
		if (temp[i]->getType() == ObjectType::enemy || temp[i]->getType() == ObjectType::boulder || temp[i]->getType() == ObjectType::player) {
			collided = collisionCheck(getBounds(), temp[i]->getBounds());
		}
		if (collided == true) {
			handleCollision(temp[i]);
			break;
		}
	}

	if (x < 0 || collided) {
		x += PLAYER_WIDTH;
		move += 1;
	}
	this->setBounds({ x, this->getBounds().y, this->getBounds().h, this->getBounds().w });

	
}

void Entity::MoveRight(std::vector<Entity*> entities, int position) {
	x += PLAYER_WIDTH;
	move -= 1;
	this->setBounds({ x, this->getBounds().y, this->getBounds().h, this->getBounds().w });
	std::vector<Entity*> temp = entities;
	temp.erase(temp.begin() + position);
	bool collided = false;
	for (int i = 0; i < temp.size(); ++i) {
		if (temp[i]->getType() == ObjectType::enemy || temp[i]->getType() == ObjectType::boulder || temp[i]->getType() == ObjectType::player) {
			collided = collisionCheck(getBounds(), temp[i]->getBounds());
		}
		if (collided == true) {
			handleCollision(temp[i]);
			break;
		}
	}


	if (x + PLAYER_WIDTH > BASE_WIDTH || collided) {
		x -= PLAYER_WIDTH;
		move += 1;
	}
	this->setBounds({ x, this->getBounds().y, this->getBounds().h, this->getBounds().w });

}

void Entity::Die() {
	if (getHealth() <= 0) {

	}
}

bool Entity::mouseCheck() {
	float mouseX = -1.f, mouseY = -1.f;
	SDL_GetMouseState(&mouseX, &mouseY);
	bool hoveringOnEntity = true;
	if (mouseX < getBounds().x) {
		hoveringOnEntity = false;
	}
	else if (mouseX > (getBounds().x + PLAYER_WIDTH)) {
		hoveringOnEntity = false;
	}
	else if (mouseY < getBounds().y) {
		hoveringOnEntity = false;
	}
	else if (mouseY > (getBounds().y + PLAYER_HEIGHT)) {
		hoveringOnEntity = false;
	}
	return hoveringOnEntity;
}

//pass in entities vector? pass vector along to move functions? 
void Entity::playerInput(SDL_Event& e, std::vector<Entity*> entities) {
	if (getEntityTurn() == 1) {
		const bool* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_UP] && !(state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_LEFT])) {
			setSpeed(5);
			MoveUp(entities, 0);
		}
		else if (state[SDL_SCANCODE_DOWN] && !(state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_LEFT])) {
			setSpeed(5);
			MoveDown(entities, 0);

		}
		else if (state[SDL_SCANCODE_RIGHT] && !(state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN])) {
			setSpeed(5);
			MoveRight(entities, 0);
		}
		else if (state[SDL_SCANCODE_LEFT] && !(state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN])) {
			setSpeed(5);
			MoveLeft(entities, 0);

		}
		else if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_DOWN]) {
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
	if (getType() == ObjectType::player) {
		SDL_SetRenderDrawColor(window.renderer, 85, 0, 145, 255);
	}
	else if (getType() == ObjectType::tile && !(pos)) {
		SDL_SetRenderScale(window.renderer, SCALAR * 3, SCALAR * 3);
		SDL_SetRenderDrawColor(window.renderer, 255, 255, 255, 255);
	}
	else if (getType() == ObjectType::tile && pos) {
		SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
	}
	else {
		SDL_SetRenderDrawColor(window.renderer, 155, 0, 20, 255);
	}
	if ((getX() + PLAYER_WIDTH) / SCALAR >= WINDOW_WIDTH / SCALAR || (getX() + ((len / 2) * 8)) / SCALAR >= WINDOW_WIDTH / SCALAR) {
		xpos = WINDOW_WIDTH - (len * (8 * SCALAR));
	}
	else if (getX() / SCALAR == 0 || (getX() - ((len / 2) * 8) + PLAYER_WIDTH) / SCALAR < 0) {
		xpos = 0;
	}
	else if (getType() == ObjectType::tile) {
		xpos = WINDOW_WIDTH/60;
	}
	else {
		xpos = getX() - ((len / 2) * 8) + (PLAYER_WIDTH / 2);
	}
	if (getY() == 0 || pos) {
		ypos = getY() + PLAYER_HEIGHT;
	}
	else if (getType() == ObjectType::tile) {
		ypos = WINDOW_HEIGHT / 7;
	}
	else {
		ypos = getY() - PLAYER_HEIGHT / 2;
	}
	if (!(0 <= xpos <= WINDOW_WIDTH) || !(0 <= ypos <= WINDOW_HEIGHT)) {
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
	SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);

}