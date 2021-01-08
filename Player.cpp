#include "Player.h"
#include "TextureManager.h"
#include "Game.h"
#include <iostream>
using namespace std;


Player::Player(const char* path, SDL_Renderer* renderer) : renderer(renderer)
{
    map = getMap();
    frost.freeze = frost.freezeCooldown = false;
    timeHelper = 0;
    alive = true;
	setTex(path);
}

Player::~Player()
{
    //cout << "\nRIP";
    alive = false;

    SDL_DestroyTexture(texture);
    
    // afiseaza mesaj de moarte
    // retry? quit?
}

void Player::setTex(const char* path)
{

	texture = TextureManager::LoadTexture(path, renderer);
}

void Player::init()
{    
    map = getMap();
    lastKeyPressed = 0;
    speed = 0;
    HP = 100;
    alive = true;
    frost.freeze = frost.freezeCooldown = false;

    velocity.x = velocity.y = 0;

	srcRect.x = srcRect.y = 0;
	srcRect.w = srcRect.h = 32;
	destRect.w = destRect.h = 64;

}

void Player::init(int x, int y)
{
    map = getMap();
    lastKeyPressed = 0;

    HP = 100;
    alive = true;
    frost.freeze = frost.freezeCooldown = false;

    velocity.x = velocity.y = 0;

	destRect.x = x;
	destRect.y = y;
	srcRect.w = srcRect.h = 32;
	destRect.w = destRect.h = 64; // w x h imagine - cat de mare sa fie

}

void Player::update()
{
    
}

void Player::draw()
{
	TextureManager::Draw(texture, srcRect, destRect, renderer);
}

bool Player::getFrozen()
{
    return (frost.freeze && frost.freezeCooldown);
}

bool Player::getFrostFreeze()
{
    return frost.freeze;
}

bool Player::getFrostFreezeCooldown()
{
    return frost.freezeCooldown;
}

bool Player::getState()
{
    return alive;
}

// type = the type of the terrain 0, 1, 2, 3 etc.
bool Player::isAreaBlocked(int type)
{
    int x1 = destRect.x / 32;
    int x2 = (destRect.x + 31) / 32;
    int y1 = destRect.y / 32;
    int y2 = (destRect.y + 31) / 32;

    for (int y = y1; y <= y2; ++y)
    {
        for (int x = x1; x <= x2; ++x)
        {
            //cout << map[y][x] << "\n";
            if (map[y][x] == type)
            {
                return true;
            }
        }
    }
    return false;
}

int Player::getDirection()
{
    // yep, it's the velocity that dictates our direction, not the destRect
    if (velocity.x > 0)
    {
        if (velocity.y == 0)
            return 4;
        if (velocity.y > 0)
            return 7;
        return 2;
    }
    if (velocity.x == 0)
    {
        if (velocity.y == 0)
            return -1;
        if (velocity.y > 0)
            return 6;
        return 1;
    }
    if (velocity.x < 0)
    {
        if (velocity.y == 0)
            return 3;
        if (velocity.y > 0)
            return 5;
        return 0;
    }
}

int Player::getLastKeyPressed()
{
    return lastKeyPressed;
}

int Player::getTimeHelper()
{
    return timeHelper;
}

int Player::getSpeed()
{
    return speed;
}

SDL_Rect Player::getPos()
{
    return destRect;
}

SDL_Rect Player::getSafePos()
{
    return safePos;
}

SDL_Rect Player::getVelocity()
{
    return velocity;
}

void Player::setDirection(SDL_Rect x)
{

}

void Player::setFrostFreeze(bool tmp)
{
    frost.freeze = tmp;
}

void Player::setFrostFreezeCooldown(bool tmp)
{
    frost.freezeCooldown = tmp;
}


void Player::setState(bool tmp)
{
    alive = tmp;
}

void Player::setLastKeyPressed(int k)
{
    lastKeyPressed = k;
}

void Player::setTimeHelper(int t)
{
    timeHelper = t;
}

void Player::setSpeed(int x)
{
    speed = x;
}

void Player::setPos(SDL_Rect x)
{
    this->destRect.x = x.x;
    this->destRect.y = x.y;
}

void Player::setPosCoord(int x, int y)
{
    this->destRect.x = x;
    this->destRect.y = y;
}

void Player::setSafePos(SDL_Rect x)
{
    safePos.x = x.x;
    safePos.y = x.y;
}

void Player::setVelocity(SDL_Rect x)
{
    this->velocity.x = x.x;
    this->velocity.y = x.y;
}