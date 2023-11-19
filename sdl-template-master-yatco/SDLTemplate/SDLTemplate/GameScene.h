#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Background.h"
#include "Player.h"
#include "Explosion.h"
#include "Enemy.h"
#include <vector>
#include "text.h"
#include "PowerUpgrade.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
private:
	Background* background;
	Player* player;
	Explosion* explosion;
	PowerUpgrade* powerupgrade;

	//Enemy spawning logic
	float spawnTime;
	float currentSpawnTimer;
	float explosionTime;
	std::vector<Enemy*> spawnedEnemies;
	std::vector<Explosion*> spawnedExplosions;

	float waveCounter;
	float powerUpgradeSpawn;

	void doSpawnLogic();
	void doCollisionLogic();
	void spawn();
	void despawnEnemy(Enemy* enemy);

	int points;
};

