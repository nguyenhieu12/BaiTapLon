#include "Explosion.h"

Explosion::Explosion()
{
    expTexWidth = 0;
	expTexHeight = 0;
	expPosX = 0;
	expPosY = 0;
	expFrame = 0;
}

Explosion::~Explosion()
{

}

bool Explosion::loadExpImg(string expPath, SDL_Renderer* render)
{
	SDL_Surface* newExpSurface = IMG_Load(expPath.c_str());

	SDL_Texture* newExpTexture = NULL;

	if (newExpSurface != NULL)
	{
		newExpTexture = SDL_CreateTextureFromSurface(render, newExpSurface);
		if (newExpTexture == NULL)
		{
			cout << "Khong tai duoc ExpImg: " << SDL_GetError();
		}
		else
		{
			expTexWidth = newExpSurface->w / NUMBER_FRAME;
			expTexHeight = newExpSurface->h;
		}
		SDL_FreeSurface(newExpSurface);
	}
	expImg = newExpTexture;

	return expImg != NULL;
}

void Explosion::expRender(SDL_Renderer* render)
{
	SDL_Rect* currenClip = &clip[expFrame];
	SDL_Rect clipQuad = { expPosX, expPosY, expTexWidth, expTexHeight };
	if (currenClip != NULL)
	{
		clipQuad.w = currenClip->w;
		clipQuad.h = currenClip->h;
	}
	SDL_RenderCopy(render, expImg, currenClip, &clipQuad);
}

void Explosion::setExpPos(int pos_x, int pox_y)
{
	expPosX = pos_x;
	expPosY = pox_y;
}

void Explosion::setClip()
{
	clip[0].x = 0;
	clip[0].y = 0;
	clip[0].w = expTexWidth;
	clip[0].h = expTexHeight;

	clip[1].x = expTexWidth;
	clip[1].y = 0;
	clip[1].w = expTexWidth;
	clip[1].h = expTexHeight;

	clip[2].x = expTexWidth * 2;
	clip[2].y = 0;
	clip[2].w = expTexWidth;
	clip[2].h = expTexHeight;

	clip[3].x = expTexWidth * 3;
	clip[3].y = 0;
	clip[3].w = expTexWidth;
	clip[3].h = expTexHeight;
}

int Explosion::getExpWidth()
{
	return expTexWidth;
}

int Explosion::getExpHeight()
{
	return expTexHeight;
}