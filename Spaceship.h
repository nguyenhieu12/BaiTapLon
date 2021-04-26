#pragma once
#ifndef SPACESHIP__H_
#define SPACESHIP__H

#include "Base.h"

class Spaceship
{
public:

    Spaceship();
    ~Spaceship();

    bool loadSpaceshipImg(string spaceshipPath, SDL_Renderer* render);

    void freeSpaceship();

    void setSpaceshipPos(int posx, int posy);

    void spaceshipRender(SDL_Renderer* render);

    void handleInput(SDL_Event& event, SDL_Renderer* render);

    void spaceshipMove();

    SDL_Rect getSpaceshipRect();
    int getPosX();
    int getPosY();
    int getSpaceshipWidth();
    int getSpaceshipHeight();

private:

    SDL_Texture* spaceshipImg;

    int spaceshipTexWidth;
    int spaceshipTexHeight;
    int ssPosX;
    int ssPosY;
    int velX;
    int velY;

};

#endif // SPACESHIP__H_