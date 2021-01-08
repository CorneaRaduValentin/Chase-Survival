#include "SDL.h"
#include "Game.h"
#include <iostream>

Game* game = nullptr;

int main(int argc, char* argv[])
{

	// pun delay la actiunile obiectelor, ca sa nu se miste chiar asa rapid
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime; //const int?

	game = new Game();
	game->init("Project: Chase Survival",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1024, //width
		800, //height
		false);

	while (game->running())
	{
		

		frameStart = SDL_GetTicks();
		frameTime = SDL_GetTicks() - frameStart;


		game->handleEvents();
		game->update();
		game->render();

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	delete game;
	return 0;
}