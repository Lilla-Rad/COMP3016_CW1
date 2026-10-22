#include "GameState.h"
#include <iostream>

void GameState::combat(Entity* a, Entity* b)
{
	int damage = 0;
	if (player->getAvoid() > enemy->getStrength()) {
		damage = 0;
		std::cout << "Attack missed!";
	}
	else if (player->getAvoid() <= enemy->getStrength()) {
		damage = 20;
		//std::rand;
		//damage calculations, inject some level of randomness
	}
	else {
		damage = 20;
	}
	std::cout << damage;
	int newHealth = player->getHealth() - damage;
	player->setHealth(newHealth);
}
