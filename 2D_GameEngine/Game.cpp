#include"Game.h"
#include"TextureManager.h"
// #include "GameObject.h"
#include "Map.h"

#include "ECS.h"
#include "Component.h"

//GameObject* player;
//GameObject* enemy;
Map* map;

Manager manager;
auto& player(manager.addEntity());

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window Created..." << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 141, 99, 165, 1);
			std::cout << "Renderer Created..." << std::endl;
		}

		isRunning = true;

	}
	else {
		isRunning = false;
	}

	/*player = new GameObject("C:/Dev/2D_GameEngine/2D_GameEngine/assets/player.png", renderer, 0, 0);
	enemy = new GameObject("C:/Dev/2D_GameEngine/2D_GameEngine/assets/enemy.png", renderer, 50, 50);*/
	map = new Map(renderer);

	/*newPlayer.addComponent<PositionComponent>();
	newPlayer.getComponent<PositionComponent>().setPos(500, 500);*/
	player.addComponent<PositionComponent>(100, 500);
	
	std::cout << player.getComponent<PositionComponent>().y() << std::endl;
	player.addComponent<SpriteComponent>("assets/player.png", renderer);
	std::cout << player.getComponent<PositionComponent>().y() << std::endl;
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event); //& indicates the reference of the event, so won't be traced
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();

	cnt++;
	/*player->Update();
	enemy->Update();
	manager.update();
	std::cout << newPlayer.getComponent<PositionComponent>().x() << "," <<
		newPlayer.getComponent<PositionComponent>().y() << std::endl;*/
	// std::cout << cnt << std::endl;
}

void Game::render()
{
	SDL_RenderClear(renderer);
	//this is where we would add stuff to render
	map->DrawMap();
	manager.draw();
	/*player->Render();
	enemy->Render();*/
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit;
	std::cout << "Game Cleaned..." << std::endl;
}