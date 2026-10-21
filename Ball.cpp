#include "Ball.h"
#include <SDL3/SDL.h>

void Ball::update(int leftX, int leftY, int rightX, int rightY) {
	x += velX;
	y += velY;
	
	if (y <= 0 || y >= WINDOW_HEIGHT - BALL_SIZE) {
		velY = -velY;
	}

	if (x <= 0) {
		x = WINDOW_WIDTH / 2 - BALL_SIZE / 2;
		y = WINDOW_HEIGHT / 2 - BALL_SIZE / 2;
		velX = BALL_SPEED;
		velY = BALL_SPEED;
	}

	if (x >= WINDOW_WIDTH-BALL_SIZE) {
		x = WINDOW_WIDTH / 2 - BALL_SIZE / 2;
		y = WINDOW_HEIGHT / 2 - BALL_SIZE / 2;
		velX = -BALL_SPEED;
		velY = -BALL_SPEED;
	}

	if (x <= PADDLE_WIDTH && y >= leftY && y <= leftY + PADDLE_HEIGHT) {
		velX = BALL_SPEED;
	}


	if (x >= WINDOW_WIDTH-PADDLE_WIDTH-BALL_SIZE && y >= rightY && y <= rightY + PADDLE_HEIGHT) {
		velX = -BALL_SPEED;
	}
};