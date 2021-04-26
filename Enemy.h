#pragma once
#ifndef ENEMY__H_
#define ENEMY__H_

#include "Base.h"
#include "Bullet.h"
#include "Explosion.h"

class Enemy
{
public:

	Enemy();
	~Enemy();

	void freeEnemy();

	bool loadEnemyImg(string enemyPath, SDL_Renderer* render);

	void enemyMove();

	void setEnemyPos(int PosX, int PosY);

	void enemyRender(SDL_Renderer* render);

	void createBullet(SDL_Renderer* render, Bullet* new_bullet);

	bool autoShot(SDL_Renderer* render, int limitX, int limitY, const SDL_Rect& spaceshipRect, Explosion explosion);

	void createEnemy(SDL_Renderer* render, Enemy* newEnemy, int numberEnemy);

	bool enemyAttack(SDL_Renderer* render, SDL_Window* window, Enemy* newEnemy, int numberEnemy, const SDL_Rect& spaceshipRect,
		vector<Bullet*> bullet_list, Mix_Chunk* explosionSound, Explosion explosion, int& markValue);

	bool checkColSpaceAndEnemy(const SDL_Rect& spaceshipRect, const SDL_Rect& enemyRect);

	bool checkColSBAndEnemy(const SDL_Rect& bulletRect, const SDL_Rect& enemyRect);

	void checkColBulletVsEnemy(vector<Bullet*> bullet_check, Enemy* colEnemy, const SDL_Rect& enemyRect,
		int reset, Mix_Chunk* explosionSound, SDL_Renderer* render, Explosion explosion, int& markValue);

	void resetEnemy(int e_reset);

	void resetAllEnemy(Enemy* allEnemy, int numOfEnemy);

	void resetBullet(Bullet* bullet_);

	SDL_Rect getEnemyRect();
	vector<Bullet*> getEnemyBulletList() const { return enemyBulletList; }
	int getEnemyTexWidth();
	int getEnemyTexHeight();
	int getEnemyPosX();
	int getEnemyPosY();

private:

	SDL_Texture* enemyImg;

	vector<Bullet*> enemyBulletList;

	int enemyTexWidth;
	int enemyTexHeight;
	int posX;
	int posY;
	int enemyVel;

};

#endif // ! ENEMY__H_

