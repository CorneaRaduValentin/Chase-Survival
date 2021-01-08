#pragma once
#include "Player.h"

class PlayerGood : public Player
{
private:
	//ar fi trebuit sa numar totalul de jucatori buni in viata si, pe baza lor, sa stabilesc daca resetez nivelul si alte lucruri
	static int countGoodPlayers;

	//int APP;
	
public:
	PlayerGood() = default;
	PlayerGood(const char* path, SDL_Renderer* renderer);
	~PlayerGood();
};