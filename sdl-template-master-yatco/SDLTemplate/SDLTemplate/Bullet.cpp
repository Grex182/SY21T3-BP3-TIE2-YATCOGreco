#include "Bullet.h"

Bullet::Bullet(float positionX, float positionY, float directionX, float directionY, float speed)
{
	this->x = positionX;
	this->y = positionY;
	this->directionX = directionX;
	this->directionY = directionY;
	this->speed = speed;
}

void Bullet::start()
{
	width = 0;
	height = 0;
	texture = loadTexture("gfx/playerBullet.png");

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Bullet::update()
{
	x += directionX * speed;
	y += directionY * speed;
}

void Bullet::draw()
{
	blit(texture, x, y);
}

float Bullet::getPositionX()
{
	return x;
}

float Bullet::getPositionY()
{
	return y;
}

float Bullet::getWidth()
{
	return width;
}

float Bullet::getHeight()
{
	return height;
}
