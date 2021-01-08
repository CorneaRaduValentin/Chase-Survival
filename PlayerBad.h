#pragma once
#include "Player.h"
#include "PlayerGoodHuman.h"

class PlayerBad : public Player
{
private:
	
	bool isHitting;
	bool isFrozen;


	
	int timeHelper;

public:
	PlayerBad(const char* path, SDL_Renderer* renderer, int speed);
	~PlayerBad();

	void update(int time, PlayerGoodHuman& x);
	
	friend bool checkCollision_PlayerGood(SDL_Rect a, SDL_Rect b);
};