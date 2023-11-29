#include "GameScene.h"

GameScene::GameScene() : window(nullptr), renderer(nullptr)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
	// Register and add game objects on constructor
}

GameScene::~GameScene()
{

}

void GameScene::start()
{
	Scene::start();

	SDL_Rect head{ 500, 500, 10, 10 };

	size = 1;
	dir = 0;
	health = 3;
	points = 0;

	running = true;

	// Initialize any scene logic here
}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::update()
{
	Scene::update();
	spawnApples();

	gameLoop();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void GameScene::Screen()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	auto window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);
	auto renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event e;
}

void GameScene::checkInput()
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_DOWN) { dir = DOWN; }
			else if (e.key.keysym.sym == SDLK_UP) { dir = UP; }
			else if (e.key.keysym.sym == SDLK_LEFT) { dir = LEFT; }
			else if (e.key.keysym.sym == SDLK_RIGHT) { dir = RIGHT; }
		}
	}
}

void GameScene::gameLoop()
{
	//Main Loop
	while (running)
	{
		checkInput();

		//Move snake in Direction
		switch (dir)
		{
		case DOWN:
			head.y += 10;
			break;
		case UP:
			head.y -= 10;
			break;
		case LEFT:
			head.x -= 10;
			break;
		case RIGHT:
			head.x += 10;
			break;
		}

		//Collision Detection with apple
		std::for_each(apples.begin(), apples.end(), [&](auto& apple) {
			if (head.x == apple.x && head.y == apple.y)
			{
				size += 2;
				apple.x = -10;
				apple.y = -10;
				points++;
			}
			});

		//Collision detection with snake body
		std::for_each(rq.begin(), rq.end(), [&](auto& snake_segment) {
			if (head.x == snake_segment.x && head.y == snake_segment.y)
			{
				size = 1;
				health--;

				if (health == 0)
				{
					running = false;
				}
			}
			});

		//add newest head to the snake
		rq.push_front(head);

		while (rq.size() > size)
			rq.pop_back();



		//Clear The Window
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Draw apples in red color
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
		std::for_each(apples.begin(), apples.end(), [&](auto& apple)
			{
				SDL_RenderFillRect(renderer, &apple);
			});


		//Draw body
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		std::for_each(rq.begin(), rq.end(), [&](auto& snake_segment)
			{
				SDL_RenderFillRect(renderer, &snake_segment);
			});

		//Display
		SDL_RenderPresent(renderer);
		SDL_Delay(25);

	}
}

void GameScene::spawnApples()
{
	for (int i = 0; i < 80; i++)
	{
		SDL_Rect appleRect;
		appleRect.x = rand() % 100 * 10;
		appleRect.y = rand() % 100 * 10;
		appleRect.w = 10;
		appleRect.h = 10;
		apples.push_back(appleRect);
	}
}
