#include "PlayerGoodHuman.h"
#include <iostream>
#include <cstdlib>
#include "Game.h"

using namespace std;


PlayerGoodHuman::PlayerGoodHuman(const char* path, SDL_Renderer* renderer) : PlayerGood(path, renderer)
{
    setSpeed(7);
    timeSurvived = 0;
}

PlayerGoodHuman::~PlayerGoodHuman()
{
    //PlayerGood::~PlayerGood();
    timeSurvived = 0;
}


void PlayerGoodHuman::update()
{
    ++timeSurvived;
    // 2900 == 1 minut
    // 1450 == 30 secunde
    // 484 == 10 secunde
    // 145 == 3 secunde
    // cout << timeSurvived << "\n";

    int speed = getSpeed();

    SDL_Rect velocity = getVelocity();
    SDL_Rect destRect = getPos();
    SDL_Rect safePos = getSafePos();

    if (isAreaBlocked(3) == true || isAreaBlocked(0) == true || isAreaBlocked(6) == true)
    {
        destRect.x = safePos.x;
        destRect.y = safePos.y;
        setPos(destRect);

    }

    if (isAreaBlocked(2) == true)
        setSpeed(10);

    if (isAreaBlocked(1) == true)
        setSpeed(7);

    if (isAreaBlocked(5) == true)
        setSpeed(5);

    if (isAreaBlocked(4) == true)
        setSpeed(8);

    ++timeHelper;
    if (timeHelper == 60 && getFrostFreezeCooldown() == false && getFrostFreeze() == false)
    {
        setFrostFreezeCooldown(true);
        timeHelper = 0;
    }

    

    if (Game::event.type == SDL_KEYDOWN)
    {
        switch (Game::event.key.keysym.sym)
        {
        case SDLK_LEFT:
            velocity.x = -speed;
            break;
        case SDLK_RIGHT:
            velocity.x = speed;
            break;
        case SDLK_UP:
            velocity.y = -speed;
            break;
        case SDLK_DOWN:
            velocity.y = speed;
            break;
            
        case SDLK_SPACE:
            if (getFrostFreezeCooldown() == true)
            {
                setFrostFreeze(true);
                timeHelper = 0;
            }
            break;
        default:
            break;
        }
    }
    else if (Game::event.type == SDL_KEYUP)
    {
        switch (Game::event.key.keysym.sym)
        {
        case SDLK_LEFT:
            if (velocity.x < 0)
            {
                velocity.x = 0;
                
            }
            break;
        case SDLK_RIGHT:
            if (velocity.x > 0)
            {
                velocity.x = 0;
                
            }
            break;
        case SDLK_UP:
            if (velocity.y < 0)
            {
                velocity.y = 0;
                
            }
            break;
        case SDLK_DOWN:
            if (velocity.y > 0)
            {
                velocity.y = 0;
                
            }
            break;
        default:
            break;
        }
    }
    if (timeHelper == 60)
    {
        timeHelper = 0;
    }
    safePos.x = destRect.x;
    safePos.y = destRect.y;
    setSafePos(safePos);


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

    setLastKeyPressed(getDirection());
    int lkp = 0;
    switch (getLastKeyPressed())
    {
    case -1:
        if (timeHelper == 0)
        {
            lkp = rand() % 5;
            switch (lkp) // vreau sa fie un texture mai des decat celelalte - as fi putut face un sprite pentru eficienta, dar am ales sa dau load fisierelor de fiecare data pentru ca imi vine mai usor
            {
            case 0:
            case 1:
                //cout << lkp;
                setTex("assets/human/humanIdle/humanIdle0.png");
                break;
            case 2:
            case 3:
                //cout << lkp;
                setTex("assets/human/humanIdle/humanIdle1.png");
                break;
            default:
                //cout << lkp;
                setTex("assets/human/humanIdle/humanIdle2.png");
                break;
            }
        }
        break;
    case 1:
        lkp = timeHelper;
        {
            if (lkp < 20)
                setTex("assets/human/humanUp/up1.png");
            if (lkp >= 20 && lkp < 40)
                setTex("assets/human/humanUp/up2.png");
            if (lkp >= 40)
                setTex("assets/human/humanUp/up3.png");
        }
        break;
    case 6:
        lkp = timeHelper;
        {
            if (lkp < 20)
                setTex("assets/human/humanDown/down1.png");
            if (lkp >= 20 && lkp < 40)
                setTex("assets/human/humanDown/down2.png");
            if (lkp >= 40)
                setTex("assets/human/humanDown/down3.png");
        }
        break;

    case 2:
    case 4:
    case 7:
            lkp = timeHelper;
            if (lkp < 10)
            {
                //cout << lkp;
                setTex("assets/human/humanRight/left1.png");
            }
            if (lkp >= 10 && lkp < 20)
            {
                //cout << lkp;
                setTex("assets/human/humanRight/left2.png");
            }
            if (lkp >= 20 && lkp < 30)
            {
                //cout << lkp;
                setTex("assets/human/humanRight/left3.png");
                break;
            }
            if (lkp >= 30 && lkp < 40)
            {
                //cout << lkp;
                setTex("assets/human/humanRight/left4.png");
            }
            if (lkp >= 40 && lkp < 50)
            {
                //cout << lkp;
                setTex("assets/human/humanRight/left5.png");
            }
            if (lkp >= 50)
            {
                //cout << lkp;
                setTex("assets/human/humanRight/left6.png");
            }
            break;

    default:
        lkp = timeHelper;
        if (lkp < 10)
        {
            //cout << lkp;
            setTex("assets/human/humanLeft/left1.png");
        }
        if (lkp >= 10 && lkp < 20)
        {
            //cout << lkp;
            setTex("assets/human/humanLeft/left2.png");
        }
        if (lkp >= 20 && lkp < 30)
        {
            //cout << lkp;
            setTex("assets/human/humanLeft/left3.png");
            break;
        }
        if (lkp >= 30 && lkp < 40)
        {
            //cout << lkp;
            setTex("assets/human/humanLeft/left4.png");
        }
        if (lkp >= 40 && lkp < 50)
        {
            //cout << lkp;
            setTex("assets/human/humanLeft/left5.png");
        }
        if (lkp >= 50)
        {
            //cout << lkp;
            setTex("assets/human/humanLeft/left6.png");
        }
        break;
    }
    setVelocity(velocity);
    setPos(destRect);
}


void PlayerGoodHuman::setTimeSurvived(int x)
{
    timeSurvived = x;
}

int PlayerGoodHuman::getTimeSurvived()
{
    return timeSurvived;
}