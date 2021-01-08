#include "GameObject.h"
#include "PlayerGoodHuman.h"
#include "PlayerBad.h"
#include <iostream>

using namespace std;

bool GameObject::isActive()
{
	if (active)
		return true;
	return false;
}

bool checkCollision(SDL_Rect a, SDL_Rect b)
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

GameObject::GameObject(const char* textureSheet, SDL_Renderer* renderer, int x, int y)
{
	countdown = 0;
	active = true;
	timeHelper = 0;
	//switchPar = 0;

	speed = 0;

	_renderer = renderer;
	_texture = TextureManager::LoadTexture(textureSheet, _renderer);
	_x = x;
	_y = y;
}

GameObject::GameObject(const char* textureSheet, SDL_Renderer* renderer, int x, int y, int speed)
{
	countdown = 55;

	this->speed = speed;

	_renderer = renderer;
	_texture = TextureManager::LoadTexture(textureSheet, _renderer);
	_x = x;
	_y = y;
}

GameObject::~GameObject() = default;

void GameObject::Update()
{

	//Schimba pozitia obiectului
	_x++;
	_y++;

	//Care este dimensiunea obiectului
	_srcRectangle.w = 595;
	_srcRectangle.h = 450;
	_srcRectangle.x = 0;
	_srcRectangle.y = 0;

	_destRectangle.x = _x;
	_destRectangle.y = _y;// _srcRectangle.h* sin(_y);
	//Modifica L si l a pozei
	_destRectangle.w = 96; //aici FORTEZ imaginea la ce dim vreau eu
	_destRectangle.h = 96; //same si pentru height
}

/*
void GameObject::Chase(SDL_Rect destRect, int time, PlayerGoodHuman &x)
{
	timeHelper++;

	if (timeHelper == 50 * time)
	{
		cout << "\nSi-a luat freeze AUTOMAT! " << timeHelper;
		timeHelper = 0;
		switchPar = !switchPar;
		x.setFrostFreeze(0);
	}

	else if (x.getFrozen() == true && switchPar == false)
	{
		cout << "\nSi-a luat freeze MANUAL! " << timeHelper;
		timeHelper = 0;
		switchPar = !switchPar;
		x.setFrostFreezeCooldown(false);
	}
	

	if (switchPar == false)
	{
		if (_x < destRect.x)
			_x = _x + speed;

		if (_x > destRect.x)
			_x = _x - speed;

		if (_y < destRect.y)
			_y = _y + speed;

		if (_y > destRect.y)
			_y = _y - speed;

		_destRectangle.x = _x;
		_destRectangle.y = _y;
		//Modifica L si l a pozei
		//_destRectangle.w = 96; //aici FORTEZ imaginea la ce dim vreau eu
		//_destRectangle.h = 96; //same si pentru height
	}

	
	if (checkCollision(_destRectangle, destRect))
	{
		x.setState(false);
		x.~PlayerGoodHuman();
		std::cout << "\nAI FOST PRINS!";
	}
}*/

void GameObject::Render()
{
	SDL_RenderCopy(_renderer, _texture, &_srcRectangle, &_destRectangle);
}

void GameObject::setSpeed(int speed)
{
	this->speed = speed;
}