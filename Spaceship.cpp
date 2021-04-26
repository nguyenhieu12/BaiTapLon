#include "Spaceship.h"

Spaceship::Spaceship()
{
    spaceshipImg = NULL;
    spaceshipTexWidth = 0;
    spaceshipTexHeight = 0;
    ssPosX = 150;
    ssPosY = 250;
    velX = 0;
    velY = 0;
}

Spaceship::~Spaceship()
{
    freeSpaceship();
}

bool Spaceship::loadSpaceshipImg(string spaceshipPath, SDL_Renderer* render)
{
    freeSpaceship();

    SDL_Texture* newSpaceshipTexture = NULL;

    SDL_Surface* newSpaceshipSurface = IMG_Load(spaceshipPath.c_str());
    if (newSpaceshipSurface == NULL)
    {
        cout << "Khong the tai anh spaceship: " << IMG_GetError();
    }
    else
    {
        newSpaceshipTexture = SDL_CreateTextureFromSurface(render, newSpaceshipSurface);
        if (newSpaceshipTexture == NULL)
        {
            cout << "Khong the tao SpaceshipTexture: " << SDL_GetError();
        }
        else
        {
            spaceshipTexWidth = newSpaceshipSurface->w;
            spaceshipTexHeight = newSpaceshipSurface->h;
        }
        SDL_FreeSurface(newSpaceshipSurface);
    }
    spaceshipImg = newSpaceshipTexture;

    return spaceshipImg != NULL;
}

void Spaceship::freeSpaceship()
{
    if (spaceshipImg != NULL)
    {
        SDL_DestroyTexture(spaceshipImg);
        spaceshipImg = NULL;
        spaceshipTexWidth = 0;
        spaceshipTexHeight = 0;
        ssPosX = 0;
        ssPosY = 0;
        velX = 0;
        velY = 0;
    }
}

void Spaceship::setSpaceshipPos(int posx, int posy)
{
    ssPosX = posx;
    ssPosY = posy;
}

void Spaceship::spaceshipRender(SDL_Renderer* render)
{
    SDL_Rect spaceshipRect = { ssPosX, ssPosY, spaceshipTexWidth, spaceshipTexHeight };
    SDL_RenderCopy(render, spaceshipImg, NULL, &spaceshipRect);
}

void Spaceship::handleInput(SDL_Event& event, SDL_Renderer* render)
{
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            velY -= spaceshipTexHeight / 14;
            break;
        case SDLK_DOWN:
            velY += spaceshipTexHeight / 14;
            break;
        case SDLK_LEFT:
            velX -= spaceshipTexWidth / 14;
            break;
        case SDLK_RIGHT:
            velX += spaceshipTexWidth / 14;
            break;
        default:
            break;
        }
    }
    else if (event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            velY += spaceshipTexHeight / 14;
            break;
        case SDLK_DOWN:
            velY -= spaceshipTexHeight / 14;
            break;
        case SDLK_LEFT:
            velX += spaceshipTexWidth / 14;
            break;
        case SDLK_RIGHT:
            velX -= spaceshipTexWidth / 14;
            break;
        default:
            break;
        }
    }
}

void Spaceship::spaceshipMove()
{
    ssPosX += velX;
    if (ssPosX < 0 || ssPosX + spaceshipTexWidth > SCREEN_WIDTH)
    {
        ssPosX -= velX;
    }

    ssPosY += velY;
    if (ssPosY < 0 || ssPosY + spaceshipTexHeight > SCREEN_HEIGHT)
    {
        ssPosY -= velY;
    }
}

SDL_Rect Spaceship::getSpaceshipRect()
{
    SDL_Rect newspaceshipRect = { ssPosX, ssPosY, spaceshipTexWidth, spaceshipTexHeight };
    return newspaceshipRect;
}

int Spaceship::getPosX()
{
    return ssPosX;
}

int Spaceship::getPosY()
{
    return ssPosY;
}

int Spaceship::getSpaceshipWidth()
{
    return spaceshipTexWidth;
}

int Spaceship::getSpaceshipHeight()
{
    return spaceshipTexHeight;
}

