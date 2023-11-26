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
#include "Boss.h"

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
	Boss* boss;

	//Enemy spawning logic
	float spawnTime;
	float currentSpawnTimer;
	float bossSpawnTime;
	float currentBossSpawnTimer;
	float explosionTime;
	float bossHealth;
	float bossInvulnerabilityTime;
	std::vector<Enemy*> spawnedEnemies;
	std::vector<Bullet*> bulletHit;
	std::vector<Boss*> spawnedBosses;
	std::vector<Explosion*> spawnedExplosions;

	float waveCounter;
	float powerUpgradeSpawn;

	void doSpawnLogic();
	void doCollisionLogic();
	void spawn();
	void spawnBoss();
	void despawnEnemy(Enemy* enemy);
	void despawnBoss(Boss* boss);

	int points;
};

