#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	background = new Background();
	this->addGameObject(background);

	player = new Player();
	this->addGameObject(player);

	points = 0;
	waveCounter = 0;
	powerUpgradeSpawn = (rand() % 3) + 3;
}

GameScene::~GameScene()
{
	delete background;
	delete player;
}

void GameScene::start()
{
	Scene::start();

	// Initialize any scene logic here
	initFonts();
	currentSpawnTimer = 300;
	spawnTime = 300; //Spawn time of 5 seconds 300 / 60 since its running in 60fps

	for (int i = 0; i < 3; i++)
	{
		spawn();
	}
}

void GameScene::draw()
{
	Scene::draw();

	drawText(110, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);

	if (player->getIsAlive() == false)
	{
		drawText(SCREEN_WIDTH / 2, 600, 255, 255, 255, TEXT_CENTER, "GAME OVER!");
	}
}

void GameScene::update()
{
	Scene::update();
	doSpawnLogic();
	doCollisionLogic();

	if (explosionTime > 0)
	{
		explosionTime--;
	}

	//Memory manage enemies. When they reach the left side of the screen, delete them
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		if (spawnedEnemies[i]->getPositionY() > 800)
		{
			//Cache the variable so we can delete it later
			// We cant delete it after erasing from the vector (leaked pointer)
			Enemy* enemyToErase = spawnedEnemies[i];
			spawnedEnemies.erase(spawnedEnemies.begin() + i);
			delete enemyToErase;

			//We cant mutate (change our vector while looping inside it
			// this might crash on the next loop iteration
			// to counter that, we only delete one bullet per frame
			break;
		}
	}
}

void GameScene::doSpawnLogic()
{
	if (currentSpawnTimer > 0)
		currentSpawnTimer--;

	if (currentSpawnTimer <= 0)
	{
		waveCounter = waveCounter + 1;

		if (waveCounter == powerUpgradeSpawn)
		{
			powerupgrade = new PowerUpgrade();
			this->addGameObject(powerupgrade);
		}

		for (int i = 0; i < 3; i++)
		{
			spawn();
			currentSpawnTimer = spawnTime;
		}
	}
}

void GameScene::doCollisionLogic()
{
	//Check for collision
	for (int i = 0; i < objects.size(); i++)
	{
		//Cast to bullet
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);

		//Cast to PowerUpgrade
		PowerUpgrade* powerupgrade = dynamic_cast<PowerUpgrade*>(objects[i]);

		//Cast to Explosion
		Explosion* explosion = dynamic_cast<Explosion*>(objects[i]);

		if (explosion != NULL)
		{
			if (explosionTime <= 0)
			{
				delete explosion;
			}
		}

		if (powerupgrade != NULL)
		{
			int collision = checkCollision(
				player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
				powerupgrade->getPositionX(), powerupgrade->getPositionY(), powerupgrade->getWidth(), powerupgrade->getHeight()
			);

			if (collision == 1)
			{
				std::cout << "Player has upgraded!" << std::endl;

				delete powerupgrade;
			}
		}

		//Check if the cast was successful (i.e. objects[i] is a Bullet)
		if (bullet != NULL)
		{
			//If the bullet is the enemy side, check against the player
			if (bullet->getSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision(
					player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
					bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
				);

				//Player gets hit
				if (collision == 1)
				{
					player->doDeath();

					explosion = new Explosion(player->getPositionX(), player->getPositionY());
					this->addGameObject(explosion);

					break;
				}
			}
			//If the bullet is from the player side, check against ALL enemies
			else if (bullet->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedEnemies.size(); i++)
				{
					Enemy* currentEnemy = spawnedEnemies[i];

					int collision = checkCollision(
						currentEnemy->getPositionX(), currentEnemy->getPositionY(), currentEnemy->getWidth(), currentEnemy->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
					);

					if (collision == 1)
					{
						Explosion* explosion = new Explosion(currentEnemy->getPositionX(), currentEnemy->getPositionY());
						this->addGameObject(explosion);
						
						explosionTime = 60;

						despawnEnemy(currentEnemy);

						//Increment points
						points++;
						//IMPORTANT: only despawn one at a time,
						//otherwise we might crash due to looping while deleting
						break;
					}
				}
			}
		}
	}
}

void GameScene::spawn()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition((rand() % 300) + 450, -34); //Original value was idk

	spawnedEnemies.push_back(enemy);
}

void GameScene::despawnEnemy(Enemy* enemy)
{
	int index = -1;
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		//if the pointer matches
		if (enemy == spawnedEnemies[i])
		{
			index = i;
			break;
		}
	}

	//if any matches is found
	if (index != -1)
	{

		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		delete enemy;
	}
}
