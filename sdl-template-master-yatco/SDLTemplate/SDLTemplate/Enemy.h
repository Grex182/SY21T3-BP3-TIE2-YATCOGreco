#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>;
#include "util.h";
#include "Player.h"

class Enemy : public GameObject
{
public:
    Enemy();
    ~Enemy();
    void start();
    void update();
    void draw();
    void setPlayerTarget(Player* player);
    void setPosition(int xPos, int yPos);

    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();

private:
    SDL_Texture* texture;
    Mix_Chunk* sound;
    Player* playerTarget;
    int x;
    int y;
    int width;
    int height;
    int speed;

    float directionX;
    float directionY;
    float reloadTime;
    float currentReloadTime;
    float directionChangeTime;
    float currentDirectionChangeTime;

    std::vector<Bullet*> bullets;

};

