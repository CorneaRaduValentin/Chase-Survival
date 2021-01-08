#pragma once
#include <SDL.h>
#include "SDL_image.h"
#include "TextureManager.h"

class Game
{
private:
	bool isRunning;
	int cnt = 0;
	SDL_Window* window;
	SDL_Renderer* renderer;

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update() const;
	void render() const;
	void clean() const;
	int getCNT();

	bool running() const
	{
		return isRunning;
	}

	static SDL_Event event;

};

