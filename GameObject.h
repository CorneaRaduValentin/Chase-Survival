#pragma once
#include "Game.h"
#include "Player.h"
#include "PlayerBad.h"
#include "PlayerGoodHuman.h"

class GameObject : public Game
{
private:

	int countdown;
	bool active;

	int timeHelper;
	//bool switchPar;

	int _x;
	int _y;

	int speed;

	SDL_Texture* _texture;
	SDL_Rect _srcRectangle;
	SDL_Rect _destRectangle;
	SDL_Renderer* _renderer;

public:
	bool isActive();


	void setSpeed(int speed);
	void Update();
	//void Chase(SDL_Rect destRect, int time, PlayerGoodHuman &x);
	void Render();

	GameObject(const char* textureSheet, SDL_Renderer* renderer, int x, int y, int speed);
	GameObject(const char* textureSheet, SDL_Renderer* renderer, int x, int y);
	~GameObject();

	
	friend bool checkCollision(SDL_Rect a, SDL_Rect b);
};
