#include "Player.h"
#include "Scene.h"

Player::~Player()
{
	// Memory manage our bullets. Delete all bullets on player deletetion/death
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	bullets.clear();
}

void Player::start()
{
	// Load texture
	texture = loadTexture("gfx/player.png");

	// Initialize to avoid garbage values
	x = 620;
	y = 560;
	width = 0;
	height = 0;
	speed = 3;
	reloadTime = 12; // Reload time of 8 frames, or .5 seconds, formula is: reloadtime/60fps
	currentReloadTime = 0;
	specialReloadTime = 35;
	currentSpecialReloadTime = 0;
	isAlive = true;
	poweredUp = false;

	// Query the texture to set our with and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Player::update()
{
	//Memory manage bullets. When they go off screen, delete them
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() > SCREEN_WIDTH || bullets[i]->getPositionY() > SCREEN_HEIGHT)
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

	if (!isAlive) return;
	if (app.keyboard[SDL_SCANCODE_W])
	{
		y -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += speed;
	}

	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += speed;
	}

	if (app.keyboard[SDL_SCANCODE_LSHIFT])
	{
		speed = 5;
	}

	if (app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		speed = 3;
	}

	//Decrement the player's reload timer
	if (currentReloadTime > 0)
		currentReloadTime--;

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0 && poweredUp == false)
	{

		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x - 27 + width, y - 35 + height / 2, 0, 1, -10, Side::PLAYER_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
		bullet->start();

		//After firing, reset our reload timer
		currentReloadTime = reloadTime;
	}

	else if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0 && poweredUp == true)
	{

		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x - 27 + width, y - 35 + height / 2, 0, 1, -10, Side::PLAYER_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
		bullet->start();
		SoundManager::playSound(sound);
		Bullet* powerBullet1 = new Bullet(x - 64 + width, y - 35 + height / 2, 0, 1, -10, Side::PLAYER_SIDE);
		bullets.push_back(powerBullet1);
		getScene()->addGameObject(powerBullet1);
		powerBullet1->start();
		SoundManager::playSound(sound);
		Bullet* powerBullet2 = new Bullet(x + 10 + width, y - 35 + height / 2, 0, 1, -10, Side::PLAYER_SIDE);
		bullets.push_back(powerBullet2);
		getScene()->addGameObject(powerBullet2);
		powerBullet2->start();

		//After firing, reset our reload timer
		currentReloadTime = reloadTime;
	}

	if (currentSpecialReloadTime > 0)
		currentSpecialReloadTime--;

	if (app.keyboard[SDL_SCANCODE_G] && currentSpecialReloadTime == 0 && poweredUp == false)
	{
		SoundManager::playSound(sound);
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x - 64 + width, y - 35 + height / 2, 0, 1, -10, Side::PLAYER_SIDE);
		Bullet* specialBullet = new Bullet(x + 10 + width, y - 35 + height / 2, 0, 1, -10, Side::PLAYER_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
		bullets.push_back(specialBullet);
		getScene()->addGameObject(specialBullet);
		bullet->start();
		specialBullet->start();

		//After firing, reset our reload timer
		currentSpecialReloadTime = specialReloadTime;
	}

	else if (app.keyboard[SDL_SCANCODE_G] && currentSpecialReloadTime == 0 && poweredUp == true)
	{

		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x - 27 + width, y - 35 + height / 2, 0, 1, -10, Side::PLAYER_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
		bullet->start();
		SoundManager::playSound(sound);
		Bullet* powerBullet1 = new Bullet(x - 64 + width, y - 35 + height / 2, 0, 1, -10, Side::PLAYER_SIDE);
		bullets.push_back(powerBullet1);
		getScene()->addGameObject(powerBullet1);
		powerBullet1->start();
		SoundManager::playSound(sound);
		Bullet* powerBullet3 = new Bullet(x - 101 + width, y - 35 + height / 2, 0, 1, -10, Side::PLAYER_SIDE);
		bullets.push_back(powerBullet3);
		getScene()->addGameObject(powerBullet3);
		powerBullet3->start();
		SoundManager::playSound(sound);
		Bullet* powerBullet2 = new Bullet(x + 10 + width, y - 35 + height / 2, 0, 1, -10, Side::PLAYER_SIDE);
		bullets.push_back(powerBullet2);
		getScene()->addGameObject(powerBullet2);
		powerBullet2->start();
		SoundManager::playSound(sound);
		Bullet* powerBullet4 = new Bullet(x + 47 + width, y - 35 + height / 2, 0, 1, -10, Side::PLAYER_SIDE);
		bullets.push_back(powerBullet4);
		getScene()->addGameObject(powerBullet4);
		powerBullet4->start();

		//After firing, reset our reload timer
		currentSpecialReloadTime = specialReloadTime;
	}
}

void Player::draw()
{
	if (!isAlive) return; //if player is not alive, stop the function cause if you do return in a void class, it will just end cause it has nothing to return to

	blit(texture, x, y);
}

int Player::getPositionX()
{
	return x;
}

int Player::getPositionY()
{
	return y;
}

int Player::getWidth()
{
	return width;
}

int Player::getHeight()
{
	return height;
}

bool Player::getIsAlive()
{
	return isAlive;
}

bool Player::getPowerUp()
{
	return poweredUp;
}

void Player::doDeath()
{
	isAlive = false;
}

void Player::doPoweredUp()
{
	poweredUp = true;
}
