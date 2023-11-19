#include "PowerUpgrade.h"

PowerUpgrade::PowerUpgrade()
{
}

void PowerUpgrade::start()
{
	// Load texture
	texture = loadTexture("gfx/points.png");

	// Initialize to avoid garbage values
	directionX = 1;
	directionY = 1;
	x = (rand() % 400) + 351;
	y = -34;
	width = 0;
	height = 0;
	speed = 2;
	directionChangeTime = (rand() % 100) + 100; // DIrection change time of 3-8 seconds if it was (rand() % 300) + 100, now idk the computation cause how the frik did it become 3-8 seconds like what is being divided here why am i even exist
	currentDirectionChangeTime = 0;

	// Query the texture to set our with and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void PowerUpgrade::update()
{

	x += directionX * speed;
	y += directionY * speed;

	//Basic AI, switch directions every x seconds
	if (currentDirectionChangeTime > 0)
		currentDirectionChangeTime--;

	if (currentDirectionChangeTime == 0)
	{
		//Flip directions
		directionX = -directionX;
		currentDirectionChangeTime = directionChangeTime;
	}
}

void PowerUpgrade::draw()
{
	blit(texture, x, y);
}

float PowerUpgrade::getPositionX()
{
	return x;
}

float PowerUpgrade::getPositionY()
{
	return y;
}

float PowerUpgrade::getWidth()
{
	return width;
}

float PowerUpgrade::getHeight()
{
	return height;
}
