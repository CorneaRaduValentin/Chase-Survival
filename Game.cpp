#include "Game.h"
#include <iostream>
#include "GameObject.h"
#include "Player.h"
#include "PlayerGood.h"
#include "PlayerBad.h"
#include "PlayerGoodAI.h"
#include "Map.h"

Map* map;
//GameObject* tree;//, *enemy1;

PlayerGoodHuman* Radu;

PlayerBad* zombie;
PlayerBad* ghost;
PlayerBad* monster;
PlayerBad* zombie2;
PlayerBad* ghost2;
PlayerBad* monster2;

PlayerGoodAI* Maverick;

SDL_Event Game::event;

Game::Game() : isRunning(false), window(nullptr), renderer(nullptr)
{
	
}

Game::~Game()
{
	zombie = nullptr;
	ghost = nullptr;
	monster = nullptr;
	zombie2 = nullptr;
	ghost2 = nullptr;
	monster2 = nullptr;

	Maverick = nullptr;
	Radu = nullptr;
}

// Setting Up SDL & Creating A Window
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem initialised." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}
		else
		{
			std::cout << "Error at creating the window!" << std::endl;
			std::cout << SDL_GetError() << '\n';
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //last was 0?
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // RGB Alpha
			std::cout << "Renderer created!" << std::endl;
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	map = new Map(renderer);

	//tree = new GameObject("assets/tree.png", renderer, 0, 240); // ultimele 2 arg == locul unde e pus obiectul INITIAL
	zombie = new PlayerBad("assets/Enemy2.png", renderer, 3);
	ghost = new PlayerBad("assets/Enemy3.png", renderer, 4);
	monster = new PlayerBad("assets/Enemy.png", renderer, 2);

	zombie2 = new PlayerBad("assets/Enemy2.png", renderer, 2);
	ghost2 = new PlayerBad("assets/Enemy3.png", renderer, 3);
	monster2 = new PlayerBad("assets/Enemy.png", renderer, 3);

	Radu = new PlayerGoodHuman("assets/human/humanIdle/humanIdle0.png", renderer);
	Maverick = new PlayerGoodAI("assets/Maverick.png", renderer, 0, 3);

	zombie->init(917, 42);
	ghost->init(924, 574);
	monster->init(35, 42);

	//zombie2->init(450, 600);
	//ghost2->init(450, 600);
	monster2->init(35, 574);

	Radu->init(490, 350);
	Maverick->init(300, 300);

	Radu->setSpeed(7);
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

// Aici voi updata playeri, obiecte, harti
void Game::update() const
{

	//std::cout << Radu->getPos().x << " " << Radu->getPos().y << "\n";

	if (Radu->getState() == true)
	{
		// mai intai initializez harta si in functie de nivelul ei, stabilesc si pozitia de inceput a playerilor - asa previn bug-uri
		switch (map->getLevel())
		{
		case 0:
			// estimativ
			// 2900 == 1 minut
			// 1450 == 30 secunde
			// 484 == 10 secunde
			// 145 == 3 secunde
			// 966 == 20 secunde

			if (Radu->getTimeSurvived() == 1000)
			{
				map->incLevel();
				map = new Map(renderer);

				Radu->init(34, 609);

				ghost->init(860, 595);
				monster->init(1200, 400);
				zombie->init(1200, 400);

				ghost2->init(805, 130);
				monster2->init(1200, 400);
				zombie2->init(54, 75);

				zombie2->setSpeed(3);
				ghost->setSpeed(3);
				ghost2->setSpeed(4);


				Maverick->init(150, 300);

				Radu->setTimeSurvived(0);
			}
			break;

		case 1:
			if (Radu->getTimeSurvived() == 750)
			{
				map->incLevel();
				map = new Map(renderer);

				Radu->init(640, 56);

				ghost->init(880, 70);
				monster->init(880, 230);
				zombie->init(880, 390);

				ghost2->init(90, 70);
				monster2->init(90, 230);
				zombie2->init(90, 390);


				monster->setSpeed(3);
				monster2->setSpeed(3);
				zombie->setSpeed(4);
				zombie2->setSpeed(3);
				ghost->setSpeed(3);
				ghost2->setSpeed(4);

				Maverick->init(200, 200);

				Radu->setTimeSurvived(0);
			}
			break;

		case 2:
			if (Radu->getTimeSurvived() == 500)
			{

				SDL_Quit();
				map->incLevel();
			}
		default:
			//if (map->getLevel() > 2)
				//SDL_Quit();
			break;
		}


		Maverick->update(-1, (*Radu));
		Radu->update();	


		switch (map->getLevel())
		{

		// timerele vor fi modificate si pentru dificultate
		case 0:

			zombie->setState(true);
			zombie2->setState(false);
			monster->setState(true);
			monster2->setState(true);
			ghost->setState(true);
			ghost2->setState(false);

			if (zombie->getState() == true)
			{
				zombie->update(10, (*Radu));
			}

			if (ghost->getState() == true)
			{
				ghost->update(5, (*Radu));
			}

			if (monster->getState() == true)
			{
				monster->update(20, (*Radu));
			}
			
			if (zombie2->getState() == true)
			{
				zombie2->update(6, (*Radu));
			}

			if (ghost2->getState() == true)
			{
				ghost2->update(7, (*Radu));
			}

			if (monster2->getState() == true)
			{
				monster2->update(4, (*Radu));
			}

			break;

		case 1:
			zombie->setState(false);
			zombie2->setState(true);
			monster->setState(false);
			monster2->setState(false);
			ghost->setState(true);
			ghost2->setState(true);

			if (zombie->getState() == true)
			{
				zombie->update(5, (*Radu));
			}

			if (ghost->getState() == true)
			{
				ghost->update(3, (*Radu));
			}

			if (monster->getState() == true)
			{
				monster->update(2, (*Radu));
			}

			if (zombie2->getState() == true)
			{
				zombie2->update(6, (*Radu));
			}

			if (ghost2->getState() == true)
			{
				ghost2->update(7, (*Radu));
			}

			if (monster2->getState() == true)
			{
				monster2->update(4, (*Radu));
			}
			break;

		case 2:

			zombie->setState(true);
			zombie2->setState(true);
			monster->setState(true);
			monster2->setState(true);
			ghost->setState(true);
			ghost2->setState(true);

			if (zombie->getState() == true)
			{
				zombie->update(5, (*Radu));
			}

			if (ghost->getState() == true)
			{
				ghost->update(3, (*Radu));
			}

			if (monster->getState() == true)
			{
				monster->update(2, (*Radu));
			}

			if (zombie2->getState() == true)
			{
				zombie2->update(6, (*Radu));
			}

			if (ghost2->getState() == true)
			{
				ghost2->update(7, (*Radu));
			}

			if (monster2->getState() == true)
			{
				monster2->update(4, (*Radu));
			}
			break;

		default:
			break;


		}

		/*if (zombie->getState() == true)
		{
			zombie->update(4, (*Radu));

		}
		else
		{
			zombie = new PlayerBad("assets/Enemy2.png", renderer, 3);
			zombie->init(450, 700);
		}
		*/
	}
	else
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_SPACE:

			switch (map->getLevel())
			{
			case 0:
				//std::cout << "Activat";
				map = new Map(renderer);

				Radu = new PlayerGoodHuman("assets/human/humanIdle/humanIdle0.png", renderer);
				Radu->init(490, 350);
				Maverick->init(300, 300);

				zombie->init(917, 42);
				ghost->init(924, 574);
				monster->init(35, 42);

				//zombie2->init(450, 600);
				//ghost2->init(450, 600);
				monster2->init(35, 574);

				break;

			case 1:
				//map->lowerLevel();
				map = new Map(renderer);

				Radu = new PlayerGoodHuman("assets/human/humanIdle/humanIdle0.png", renderer);
				Radu->init(34, 609);

				ghost->init(860, 595);
				monster->init(1200, 400);
				zombie->init(1200, 400);

				ghost2->init(805, 130);
				monster2->init(1200, 400);
				zombie2->init(54, 75);

				Maverick->init(200, 200);

				break;

			case 2:
				//map->lowerLevel();
				map = new Map(renderer);

				Radu = new PlayerGoodHuman("assets/human/humanIdle/humanIdle0.png", renderer);
				Radu->init(640, 56);

				ghost->init(880, 70);
				monster->init(880, 230);
				zombie->init(880, 390);

				ghost2->init(90, 70);
				monster2->init(90, 230);
				zombie2->init(90, 390);

				Maverick->init(200, 200);

				break;
			
			default:
				break;
			}

			
			
			

			break;

		default:
			break;
		}
	}
	

}


// Trebuie Randate
void Game::render() const
{
	SDL_RenderClear(renderer);
	map->DrawMap();

	//tree->Render();

	zombie->draw();
	ghost->draw();
	monster->draw();

	zombie2->draw();
	ghost2->draw();
	monster2->draw();
	
	Radu->draw();
	Maverick->draw();

	SDL_RenderPresent(renderer);
}

void Game::clean() const
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

int Game::getCNT()
{
	return cnt;
}

