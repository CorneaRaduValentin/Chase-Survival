#include <iostream>
#include "PlayerGoodAI.h"


using namespace std;


bool checkCollision_PlayerGoodHuman(SDL_Rect a, SDL_Rect b)
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

void PlayerGoodAI::setMode(int m)
{
	mode = m;
}

PlayerGoodAI::PlayerGoodAI(const char* path, SDL_Renderer* renderer, int mode, int speed) : PlayerGood(path, renderer)
{
	setSpeed(speed);
	collision = false;
	this->mode = mode;
}

PlayerGoodAI::~PlayerGoodAI()
{

}

// GoodAI nu are absolut nicio functionalitate practica in joc si nu influenteaza in vreun fel gamemplay-ul, dar e placut sa ai pe cineva care vine dupa tine si iti tine de urat, motiv pentru care l-am pastrat
void PlayerGoodAI::update(int mode, PlayerGoodHuman& x)
{
	
	//cout << mode << "\n";
	int speed = getSpeed();

	SDL_Rect velocity{};
	SDL_Rect destRect = getPos();
	SDL_Rect safePos = getSafePos();
	SDL_Rect chaseRect = x.getPos();

	//cout << velocity.x << " " << velocity.y << "\n";

	if (isAreaBlocked(3) == true || isAreaBlocked(0) == true || isAreaBlocked(6) == true)
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
	/*cout << "\ntimehelper: " << timeHelper;
	cout << "\tcollision: " << collision;
	cout << " " << lastPos.x << " " << lastPos.y;
	*/


	switch (mode)
	{
	case -1:
		
		if (timeHelper == 200)
		{
			timeHelper = 0;
			lastPos.x = destRect.x;
			lastPos.y = destRect.y;
		}

		switch (collision)
		{
		case false:
			if (destRect.x < chaseRect.x)
				velocity.x = velocity.x + speed;

			if (destRect.x > chaseRect.x)
				velocity.x = velocity.x - speed;

			if (destRect.y < chaseRect.y)
				velocity.y = velocity.y + speed;
			 
			if (destRect.y > chaseRect.y)
				velocity.y = velocity.y - speed;

			break;
		case true:
			if (timeHelper % 60 == 0)
				collision = false;

			if (destRect.x < lastPos.x)
				velocity.x = velocity.x + speed;

			if (destRect.x > lastPos.x)
				velocity.x = velocity.x - speed;

			if (destRect.y < lastPos.y)
				velocity.y = velocity.y + speed;

			if (destRect.y > lastPos.y)
				velocity.y = velocity.y - speed;

			break;
		}
		

		if (checkCollision_PlayerGoodHuman(this->getPos(), x.getPos()))
		{
			collision = true;
		}

		break;

	default:
		break;
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

	//cout << " " << destRect.x << " " << destRect.y;

	setPos(destRect);


	//cout << collision;

	
	//cout << abcd.x << " " << abcd.y << "\n";
	//cout << chaseRect.x << " " << chaseRect.y << "\n";
	//cout << velocity.x << " " << velocity.y << "\n";
	//cout << getDirection() << "\n";


	setVelocity(velocity);
	setLastKeyPressed(getDirection());
	int lkp = 0;
	int th = timeHelper % 50;
	//cout << "\n" << th;
	switch (getLastKeyPressed())
	{
	case -1:
		if (th == 0)
		{
			lkp = rand() % 5;
			switch (lkp) // vreau sa fie un texture mai des decat celelalte - as fi putut face un sprite pentru eficienta, dar am ales sa dau load fisierelor de fiecare data pentru ca imi vine mai usor
			{
			case 0:
				//cout << lkp;
				setTex("assets/playerGoodAI1/down1.png");
				break;
			}
		}
		break;
	case 1:
		//if (timeHelper == 0)
		lkp = th;
		{
			if (lkp < 12)
				setTex("assets/playerGoodAI1/up1.png");
			if (lkp >= 24 && lkp < 36)
				setTex("assets/playerGoodAI1/up1.png");
			if (lkp >= 12 && lkp < 24)
				setTex("assets/playerGoodAI1/up2.png");
			if (lkp >= 36 && lkp < 48)
				setTex("assets/playerGoodAI1/up2.png");
		}
		break;
	case 6:
		lkp = th;
		{
			if (lkp < 12)
				setTex("assets/playerGoodAI1/down1.png");
			if (lkp >= 24 && lkp < 36)
				setTex("assets/playerGoodAI1/down1.png");
			if (lkp >= 12 && lkp < 24)
				setTex("assets/playerGoodAI1/down2.png");
			if (lkp >= 36 && lkp < 48)
				setTex("assets/playerGoodAI1/down2.png");
		}
		break;


	case 2:
	case 4:
	case 7:
		// vreau sa iau totusi modelele intr-o oarecare ordine mai buna
		lkp = th;
		if (lkp < 12)
		{
			//cout << lkp;
			setTex("assets/playerGoodAI1/right1.png");
		}
		if (lkp >= 12 && lkp < 24)
		{
			//cout << lkp;
			setTex("assets/playerGoodAI1/right2.png");
		}
		if (lkp >= 24 && lkp < 36)
		{
			//cout << lkp;
			setTex("assets/playerGoodAI1/right1.png");
			break;
		}
		if (lkp >= 36 && lkp < 48)
		{
			//cout << lkp;
			setTex("assets/playerGoodAI1/right2.png");
		}
		break;

	default:
		lkp = th;
		if (lkp < 12)
		{
			//cout << lkp;
			setTex("assets/playerGoodAI1/left1.png");
		}
		if (lkp >= 12 && lkp < 24)
		{
			//cout << lkp;
			setTex("assets/playerGoodAI1/left2.png");
		}
		if (lkp >= 24 && lkp < 36)
		{
			//cout << lkp;
			setTex("assets/playerGoodAI1/left1.png");
			break;
		}
		if (lkp >= 36 && lkp < 48)
		{
			//cout << lkp;
			setTex("assets/playerGoodAI1/left2.png");
		}
		break;
	}
}