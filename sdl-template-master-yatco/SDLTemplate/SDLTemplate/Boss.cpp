#include "Boss.h"
#include "Scene.h"

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::start()
{
	// Load texture
	texture = loadTexture("gfx/enemyBoss.png");

	// Initialize to avoid garbage values
	directionX = 1;
	directionY = 0;
	width = 0;
	height = 0;
	speed = 4;
	reloadTime = 45; // Reload time of 8 frames, or .5 seconds, formula is: reloadtime/60fps
	specialReloadTime = 130;
	currentReloadTime = 0;
	currentSpecialReloadTime = 0;
	directionChangeTime = 260; // DIrection change time of 3-8 seconds if it was (rand() % 300) + 100, now idk the computation cause how the frik did it become 3-8 seconds like what is being divided here why am i even exist
	currentDirectionChangeTime = 0;

	// Query the texture to set our with and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 32; //128 is max volume
}

void Boss::update()
{
	//Move
	x += directionX * speed;
	y += directionY * speed;

	//Basic AI, switch directions every x seconds
	if (currentDirectionChangeTime > 0)
		currentDirectionChangeTime--;

	if (currentDirectionChangeTime == 150)
	{
		//Flip directions
		directionX = -directionX;
		reloadTime = 20;
	}

	else if (currentDirectionChangeTime == 140)
	{
		//Flip directions
		directionX = -directionX;
	}

	else if (currentDirectionChangeTime == 0)
	{
		//Flip directions
		directionX = -directionX;
		currentDirectionChangeTime = directionChangeTime;
		reloadTime = 45;
	}

	//Decrement the enemy's reload timer
	if (currentReloadTime > 0)
		currentReloadTime--;

	if (currentSpecialReloadTime > 0)
		currentSpecialReloadTime--;

	//Only fire when our reload timer is ready
	if (currentReloadTime == 0)
	{
		float dx = -1;
		float dy = 0;

		calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);

		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(70 + x - width, y + 20 + height / 2, dx, dy, 10, Side::BOSS_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
		bullet->start();

		//After firing, reset our reload timer
		currentReloadTime = reloadTime;
	}

	else if (currentSpecialReloadTime == 0)
	{
		float dx = 0;
		float dy = 1;

		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(70 + x - width, y + 20 + height / 2, dx, dy, 10, Side::BOSS_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
		bullet->start();
		SoundManager::playSound(sound);
		Bullet* bullet1 = new Bullet(20 + x - width, y + 20 + height / 2, dx, dy, 10, Side::BOSS_SIDE);
		bullets.push_back(bullet1);
		getScene()->addGameObject(bullet1);
		SoundManager::playSound(sound);
		Bullet* bullet2 = new Bullet(120 + x - width, y + 20 + height / 2, dx, dy, 10, Side::BOSS_SIDE);
		bullets.push_back(bullet2);
		getScene()->addGameObject(bullet2);
		bullet2->start();
		Bullet* bullet3 = new Bullet(170 + x - width, y + 20 + height / 2, dx, dy, 10, Side::BOSS_SIDE);
		bullets.push_back(bullet3);
		getScene()->addGameObject(bullet3);
		bullet3->start();
		Bullet* bullet4 = new Bullet(-30 + x - width, y + 20 + height / 2, dx, dy, 10, Side::BOSS_SIDE);
		bullets.push_back(bullet4);
		getScene()->addGameObject(bullet4);
		bullet4->start();

		//After firing, reset our reload timer
		currentSpecialReloadTime = specialReloadTime;
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

void Boss::draw()
{
	blit(texture, x, y);
}

void Boss::setPlayerTarget(Player* player)
{
	playerTarget = player;
}

void Boss::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}

int Boss::getPositionX()
{
	return x;
}

int Boss::getPositionY()
{
	return y;
}

int Boss::getWidth()
{
	return width;
}

int Boss::getHeight()
{
	return height;
}
