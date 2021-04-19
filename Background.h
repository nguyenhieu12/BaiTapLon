#pragma once
#ifndef BACKGROUND__H_
#define BACKGROUND__H_

#include "Base.h"

class Background
{
public:

    Background();
    ~Background();

    bool loadBackgroundImg(string backgroundPath, SDL_Renderer* render);

    void freeBackground();

    void renderBackground(int x, int y, SDL_Renderer* render);

    int getBackgroundWidth();
    int getBackgroundHeight();

private:

    SDL_Texture* backgroundImg;

    int backgroundTexWidth;
    int backgroundTexHeight;
};

#endif // BACKGROUND__H_