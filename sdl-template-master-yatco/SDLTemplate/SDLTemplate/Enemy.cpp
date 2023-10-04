#include "Enemy.h"
#include "Scene.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::start()
{
	// Load texture
	texture = loadTexture("gfx/enemy.png");

	// Initialize to avoid garbage values
	directionX = -1;
	directionY = 1;
	width = 0;
	height = 0;
	speed = 2;
	reloadTime = 60; // Reload time of 8 frames, or .5 seconds, formula is: reloadtime/60fps
	currentReloadTime = 0;
	directionChangeTime = (rand() % 300) + 100; // DIrection change time of 3-8 seconds if it was (rand() % 300) + 100, now idk the computation cause how the frik did it become 3-8 seconds like what is being divided here why am i even exist
	currentDirectionChangeTime = 0;

	// Query the texture to set our with and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Enemy::update()
{
	//Move
	x += directionX * speed;
	y += directionY * speed;

	//Basic AI, switch directions every x seconds
	if (currentDirectionChangeTime > 0)
		currentDirectionChangeTime--;

	if (currentDirectionChangeTime == 0)
	{
		//Flip directions
		directionY = -directionY;
		currentDirectionChangeTime = directionChangeTime;
	}

	//Decrement the enemy's reload timer
	if (currentReloadTime > 0)
		currentReloadTime--;

	//Only fire when our reload timer is ready
	if (currentReloadTime == 0)
	{
		float dx = -1;
		float dy = 0;

		calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);

		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(30 + x - width, y - 4 + height / 2, dx, dy, 10);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
		bullet->start();

		//After firing, reset our reload timer
		currentReloadTime = reloadTime;
	}

	//Memory manage bullets. When they go off screen, delete them
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() < 0)
		{
			//Cache the variable so we can delete it later
			// We cant delete it after erasing from the vector (leaked pointer)
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			//We cant mutate (change our vector while looping inside it
			// this might crash on the next loop iteration
			// to counter that, we only delete one bullet per frame
			break;
		}
	}
}

void Enemy::draw()
{
	blit(texture, x, y);
}

void Enemy::setPlayerTarget(Player* player)
{
	playerTarget = player;
}

void Enemy::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}
