#pragma once
#include "Scene.h"
#include "GameObject.h"
#include <SDL.h>
#include <vector>
#include <algorithm>
#include <deque>
#include "text.h"

enum Direction {
	DOWN, UP, LEFT, RIGHT
};

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	std::deque<SDL_Rect> rq;

	SDL_Event e;

	SDL_Rect head{ 500, 500, 10, 10 };

	std::vector<SDL_Rect> apples;

	int size;
	int dir;
	int health;
	int points;

	bool running;

	void spawnApples();
	void Screen();
	void checkInput();
	void gameLoop();
};

