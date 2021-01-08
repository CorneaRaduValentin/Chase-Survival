#pragma once
#include "PlayerGood.h"
#include "PlayerGoodHuman.h"
#include "PlayerBad.h"

class PlayerGoodAI : public PlayerGood
{
private:
	int timeHelper;
	int mode;

	SDL_Rect lastPos;
	bool collision;

public:

	void setMode(int m);
	PlayerGoodAI(const char* path, SDL_Renderer* renderer, int mode, int speed);
	~PlayerGoodAI();
	void update(int mode, PlayerGoodHuman& x);
	friend bool checkCollision_PlayerGoodHuman(SDL_Rect a, SDL_Rect b);
};