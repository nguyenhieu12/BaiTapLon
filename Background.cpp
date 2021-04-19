#include "Background.h"

Background::Background()
{
    backgroundImg = NULL;
    backgroundTexWidth = 0;
    backgroundTexHeight = 0;
}

Background::~Background()
{
    freeBackground();
}

bool Background::loadBackgroundImg(string backgroundPath, SDL_Renderer* render)
{
    freeBackground();

    SDL_Texture* newBackgroundTexture = NULL;

    SDL_Surface* newBackgroundSurface = IMG_Load(backgroundPath.c_str());

    if (newBackgroundSurface == NULL)
    {
        cout << "Khong the tai anh background: " << IMG_GetError();
    }
    else
    {
        newBackgroundTexture = SDL_CreateTextureFromSurface(render, newBackgroundSurface);
        if (newBackgroundTexture == NULL)
        {
            cout << "Khong the tao BackgroundTexture: " << SDL_GetError();
        }
        else
        {
            backgroundTexWidth = newBackgroundSurface->w;
            backgroundTexHeight = newBackgroundSurface->h;
        }

        SDL_FreeSurface(newBackgroundSurface);
    }

    backgroundImg = newBackgroundTexture;

    return backgroundImg != NULL;
}

void Background::freeBackground()
{
    if (backgroundImg != NULL)
    {
        SDL_DestroyTexture(backgroundImg);
        backgroundImg = NULL;
        backgroundTexWidth = 0;
        backgroundTexHeight = 0;
    }
}

void Background::renderBackground(int x, int y, SDL_Renderer* render)
{
    SDL_Rect backgroundQuad = { x, y, backgroundTexWidth, backgroundTexHeight };
    SDL_RenderCopy(render, backgroundImg, NULL, &backgroundQuad);
}

int Background::getBackgroundWidth()
{
    return backgroundTexWidth;
}

int Background::getBackgroundHeight()
{
    return backgroundTexHeight;
}