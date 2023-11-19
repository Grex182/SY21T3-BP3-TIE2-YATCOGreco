#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include <vector>;
#include "util.h";
#include "Player.h"


class PowerUpgrade :
    public GameObject
{
public:
    PowerUpgrade();
	void start();
	void update();
	void draw();
    float getPositionX();
    float getPositionY();
    float getWidth();
    float getHeight();

private:
    SDL_Texture* texture;

    int x;
    int y;
    int width;
    int height;
    int speed;

    float directionX;
    float directionY;
    float directionChangeTime;
    float currentDirectionChangeTime;
};

