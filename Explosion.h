#pragma once
#ifndef EXPLOSION__H_
#define EXPLOSION__H_

#include "Base.h"

const int NUMBER_FRAME = 4;

class Explosion
{
public:

	Explosion();
	~Explosion();

	bool loadExpImg(string expPath, SDL_Renderer* render);

	void expRender(SDL_Renderer* render);

	void setExp(int frame_) { expFrame = frame_; }

	void setExpPos(int pos_x, int pox_y);

	void setClip();

	int getExpWidth();
	int getExpHeight();

private:

	SDL_Texture* expImg;

	SDL_Rect clip[4];

	int expTexWidth;
	int expTexHeight;
	int expPosX;
	int expPosY;
	int expFrame;
	
};


#endif // !EXPLOSION__H_

