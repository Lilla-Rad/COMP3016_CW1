#include "Entity.h"
#include <SDL3_mixer/SDL_mixer.h>
#include <iostream>



void Entity::MoveUp(/*std::vector<Object*> colliders*/) {
	/*for (Object* i : colliders)
		std::cout << i << "";*/
	/*for (auto i = colliders.begin(); i != colliders.end(); ++i) {
		std::cout << i;
		})*/
	/*for (int i = 0; i < colliders.size(); i++) {
		//std::cout << "\n";
		//std::cout << colliders.at(i);
		Object* player = colliders.at(0);
		Object* tempObj = colliders.at(i);

		SDL_Rect tempBounds = tempObj->getBounds();
		//std::cout << tempBounds.x << tempBounds.y << tempBounds.w, tempBounds.h;
		if (collisionCheck(boundaryBox, tempBounds)) {
			std::cout << "collision detected!";
			handleCollision(this, colliders.at(i));
		}

	}*/
	if (y > 0)
		//std::cout << y - PLAYER_HEIGHT;
		y -= PLAYER_HEIGHT;
		move -= 1;

};

void Entity::MoveDown(/*SDL_Rect collider*/) {
	if (y + PLAYER_HEIGHT < WINDOW_HEIGHT)
		y += PLAYER_HEIGHT;
		move -= 1;
}

void Entity::MoveLeft(/*SDL_Rect collider*/) {
	if (x > 0)
		x -= PLAYER_WIDTH;
		move -= 1;
}

void Entity::MoveRight(/*SDL_Rect collider*/) {
	if (x + PLAYER_WIDTH < WINDOW_WIDTH)
		x += PLAYER_WIDTH;
		move -= 1;
}
	/*if (x > WINDOW_WIDTH - PLAYER_WIDTH || collisionCheck(boundaryBox, collider)) {
		x -= PLAYER_WIDTH;
		move += 1;
		//handleCollision();
	}
	/*if (collisionCheck(boundaryBox, collider)) {
		handleCollision(Entity* e, collided);
	}*/



/*void handleCollision() {

}*/


