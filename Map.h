#pragma once
#include <SDL_image.h>

class Map
{
private:
	SDL_Renderer* renderer;
	SDL_Rect src, dest;
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;
	SDL_Texture* wall;
	SDL_Texture* wood;
	SDL_Texture* lava;
	SDL_Texture* lavapop;

	int map[25][32];
	static int level;

public:
	Map() = default;
	Map(SDL_Renderer* renderer);
	~Map();

	void LoadMap(int arr[25][32]);
	void DrawMap();
	int getLevel();
	int** getMap();
	void lowerLevel();
	void incLevel();

};