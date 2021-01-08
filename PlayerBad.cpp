#include <iostream>
#include "PlayerBad.h"

using namespace std;


bool checkCollision_PlayerGood(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}



PlayerBad::PlayerBad(const char* path, SDL_Renderer* renderer, int speed) : Player(path, renderer)
{
	this->setSpeed(speed);
	setState(true);
}

PlayerBad::~PlayerBad() = default;

void PlayerBad::update(int time, PlayerGoodHuman& x)
{
	int speed = getSpeed();


	SDL_Rect velocity = getVelocity();
	SDL_Rect destRect = getPos();
	SDL_Rect safePos = getSafePos();
	SDL_Rect chaseRect = x.getPos();

	//destRect.x++;
	//setPos(destRect);
	


	if (isAreaBlocked(3) == true || isAreaBlocked(0) == true)
	{
		destRect.x = safePos.x;
		destRect.y = safePos.y;
		setPos(destRect);

		//cout << destRect.x << " " << destRect.y << "\n";

		//cout << "\nwall";
		//return;
	}

	safePos.x = destRect.x;
	safePos.y = destRect.y;
	setSafePos(safePos);




	++timeHelper;
	//cout << "\n" << getSpeed();
	if (timeHelper == 50 * time / getSpeed())
	{
		//cout << "\nSi-a luat freeze AUTOMAT! " << timeHelper;
		timeHelper = 0;
		isFrozen = !isFrozen;
		x.setFrostFreeze(0);
	}

	else if (x.getFrozen() == true && isFrozen == false)
	{
		//cout << "\nSi-a luat freeze MANUAL! " << timeHelper;
		timeHelper = 0;
		isFrozen = !isFrozen;
		x.setFrostFreezeCooldown(false);
	}




	if (isFrozen == false)
	{
		if (destRect.x < chaseRect.x)
			velocity.x = velocity.x + speed;

		if (destRect.x > chaseRect.x)
			velocity.x = velocity.x - speed;

		if (destRect.y < chaseRect.y)
			velocity.y = velocity.y + speed;

		if (destRect.y > chaseRect.y)
			velocity.y = velocity.y - speed;
	}


	if (velocity.x && velocity.y)
	{
		if (velocity.x < 0)
		{
			destRect.x -= sqrt(2) / 2 * (abs(velocity.x));
		}
		else
		{
			destRect.x += sqrt(2) / 2 * (abs(velocity.x));

		}

		if (velocity.y < 0)
		{
			destRect.y -= sqrt(2) / 2 * (abs(velocity.y));

		}
		else
		{
			destRect.y += sqrt(2) / 2 * (abs(velocity.y));

		}
	}
	else
	{
		destRect.x += velocity.x;
		destRect.y += velocity.y;
	}

	
	setPos(destRect);
	



	if (checkCollision_PlayerGood(this->getPos(), x.getPos()))
	{
		
		x.setState(false);
		x.~PlayerGoodHuman();
		//std::cout << "\nAI FOST PRINS!";
	}
	//else
	//	std::cout << "\nFugi!!!!";

}
