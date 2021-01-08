#pragma once
#include "Component.h"
#include "Map.h"
#include "SDL.h"

class Player : public Component, public Map
{
	bool alive;

	int HP;
	int lastKeyPressed;
	///  0 1 2
	///  3 x 4   x == -1 cand e pe repaus
	///  5 6 7
	int speed;
	int timeHelper;
	int xvel, yvel;

	int** map;

	struct primary
	{
		bool freeze;
		bool freezeCooldown;
	}frost;

	SDL_Texture* texture{};
	SDL_Renderer* renderer{};
	SDL_Rect srcRect{}, destRect{}; // coordonatele player-ului :)
	SDL_Rect velocity{};

	SDL_Rect safePos{};


public:
	Player() = default;
	Player(const char* path, SDL_Renderer* renderer);
	~Player();


	void setTex(const char* path);
	void init() override;
	void init(int x, int y);
	void update() override;
	void draw() override;

	
	bool getFrozen();
	bool getFrostFreeze();
	bool getFrostFreezeCooldown();
	bool getState();
	bool isAreaBlocked(int type);
	int getDirection();
	int getLastKeyPressed();
	int getTimeHelper();
	int getSpeed();
	SDL_Rect getPos();
	SDL_Rect getSafePos();
	SDL_Rect getVelocity();

	void setDirection(SDL_Rect x);
	void setFrostFreeze(bool tmp);
	void setFrostFreezeCooldown(bool tmp);
	void setState(bool tmp);
	void setLastKeyPressed(int k);
	void setTimeHelper(int t);
	void setSpeed(int x);
	void setPos(SDL_Rect x);
	void setPosCoord(int x, int y);
	void setSafePos(SDL_Rect x);
	void setVelocity(SDL_Rect x);

};
