#pragma once
#ifndef BULLET__H_
#define BULLET__H_

#include "Base.h"

class Bullet
{
public:

	Bullet();
	~Bullet();

	bool loadBulletImg(string bulletPath, SDL_Renderer* render);

	void freeBullet();

	void bulletMove(int limX, int limY);

	void bulletMoveRightToLeft();

	void bulletRender(SDL_Renderer* render);

	void setBulletPos(int PosX, int PosY);

	void handleInputBullet(SDL_Event event, SDL_Renderer* render, Mix_Chunk* laserSound, int PosX, int PosY);

	void handleBullet(SDL_Renderer* render);

	bool checkColSpaceAndEnemyBullet(const SDL_Rect& spaceshipRect, const SDL_Rect& enemyBulletRect);

	void removeBullet(const int pos);

	int getVel() const { return bulletVel; }
	void setVel(int vel) { bulletVel = vel; }

	bool getIsShot() const { return isShot; };
	void setIsShot(bool shot) { isShot = shot; }

	void setBulletList(vector<Bullet*> bullet) { bulletList = bullet; }
	vector<Bullet*> getBulletList() const { return bulletList; }
	
	SDL_Rect getBulletRect();
	int getPosX();
	int getPosY();
	int getBulletWidth();
	int getBulletHeight();

private:

	SDL_Texture* bulletImg;

	vector<Bullet*> bulletList;

	int posX;
	int posY;
	int bulletTexWidth;
	int bulletTexHeight;
	int bulletVel;
	bool isShot;

};

#endif // !BULLET__H_
