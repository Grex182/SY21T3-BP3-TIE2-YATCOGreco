#include "Explosion.h"

Explosion::Explosion(float positionX, float positionY)
{
	this->x = positionX;
	this->y = positionY;
}

void Explosion::start()
{
	//Load texture
	texture = loadTexture("gfx/explosion.png");

	//Initialize to avoid garbage values
	width = 0;
	height = 0;

	// Query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Explosion::update()
{

}

void Explosion::draw()
{
	blit(texture, x, y);
}
