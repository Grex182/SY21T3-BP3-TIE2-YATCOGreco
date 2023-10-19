#include "Background.h"

void Background::start()
{
	//Load texture
	texture = loadTexture("gfx/background2.png");

	//Initialize to avoid garbage values
	x = 0;
	y = 0;
	width = 0;
	height = 0;

	// Query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Background::update()
{
}

void Background::draw()
{
	blit(texture, x, y);
}
