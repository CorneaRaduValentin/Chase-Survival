#pragma once
#include "PlayerGood.h"

class PlayerGoodHuman : public PlayerGood
{
private:
	int timeHelper;
	int timeSurvived;

public:

	PlayerGoodHuman(const char* path, SDL_Renderer* renderer);
	~PlayerGoodHuman();
	
	void setTimeSurvived(int x);
	void update();
	int getTimeSurvived();
	
};