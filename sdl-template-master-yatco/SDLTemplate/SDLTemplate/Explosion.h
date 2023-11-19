#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

class Explosion :
    public GameObject

{
public:
    Explosion(float positionX, float positionY);
    virtual void start();
    virtual void update();
    virtual void draw();
private:
    SDL_Texture* texture;
    int x;
    int y;
    int width;
    int height;
};

