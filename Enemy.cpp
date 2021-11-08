#include "Enemy.h"

Enemy::Enemy()
{
	enemyImg = NULL;
	posX = 0;
	posY = 0;
	enemyTexWidth = 0;
	enemyTexHeight = 0;
	enemyVel = 5;
}

Enemy::~Enemy()
{
	freeEnemy();
	if (enemyBulletList.size() > 0)
	{
		for (int k = 0; k < enemyBulletList.size(); k++)
		{
			Bullet* clearBullet = enemyBulletList.at(k);
			if (clearBullet != NULL)
			{
				delete clearBullet;
				clearBullet = NULL;
			}
		}
		enemyBulletList.clear();
	}
}

void Enemy::freeEnemy()
{
	if (enemyImg != NULL)
	{
		SDL_DestroyTexture(enemyImg);
		enemyImg = NULL;
		posX = 0;
		posY = 0;
		enemyTexWidth = 0;
		enemyTexHeight = 0;
	}
}

bool Enemy::loadEnemyImg(string enemyPath, SDL_Renderer* render)
{
	SDL_Texture* enemyNewTexture = NULL;
	SDL_Surface* enemyNewSurface = IMG_Load(enemyPath.c_str());

	if (enemyNewSurface == NULL)
	{
		cout << "Khong tai duoc anh enemy: " << IMG_GetError();
	}
	else
	{
		enemyNewTexture = SDL_CreateTextureFromSurface(render, enemyNewSurface);
		if (enemyNewTexture == NULL)
		{
			cout << "Khong tao duoc enemy texture: " << SDL_GetError();
		}
		else
		{
			enemyTexWidth = enemyNewSurface->w;
			enemyTexHeight = enemyNewSurface->h;
		}
	}
    
	enemyImg = enemyNewTexture;

	return enemyImg != NULL;
}

void Enemy::enemyMove()
{
	posX -= enemyVel;
	if (posX < 0)
	{
		posX = SCREEN_WIDTH;
	}
}

void Enemy::setEnemyPos(int PosX, int PosY)
{
	posX = PosX;
	posY = PosY;
}

void Enemy::enemyRender(SDL_Renderer* render)
{
	SDL_Rect enemyQuad = { posX, posY, enemyTexWidth, enemyTexHeight };
	SDL_RenderCopy(render, enemyImg, NULL, &enemyQuad);
}

void Enemy::createBullet(SDL_Renderer* render, Bullet* new_bullet)
{
	if (new_bullet)
	{
		if (new_bullet->loadBulletImg("circle.png", render))
		{
			new_bullet->setBulletPos(posX, posY + enemyTexHeight / 2);
			new_bullet->setIsShot(true);
			enemyBulletList.push_back(new_bullet);
		}
	}
}

bool Enemy::autoShot(SDL_Renderer* render, int limitX, int limitY, const SDL_Rect& spaceshipRect, Explosion explosion)
{
	for (int i = 0; i < enemyBulletList.size(); i++)
	{
		Bullet* tempBullet = enemyBulletList.at(i);
		if (tempBullet)
		{
			if (tempBullet->getIsShot())
			{
				tempBullet->bulletMoveRightToLeft();
				tempBullet->bulletRender(render);
				if (tempBullet->checkColSpaceAndEnemyBullet(spaceshipRect, tempBullet->getBulletRect()))
				{
					return true;
				}
			}
			else
			{
				tempBullet->setIsShot(true);
				tempBullet->setBulletPos(posX, posY + enemyTexHeight / 2);
			}
		}
	}
	return false;
} 

void Enemy::createEnemy(SDL_Renderer* render, Enemy* newEnemy, int numberEnemy)
{
	for (int i = 0; i < numberEnemy; i++)
	{
		Enemy* tempEnemy = (newEnemy + i);
		if (tempEnemy)
		{
			if (!tempEnemy->loadEnemyImg("enemy_(1).png", render))
			{
				cout << "Khong tai duoc hinh anh Enemy: " << SDL_GetError();
			}
			else
			{
				int newRandY = rand() % 500;
				if (newRandY > SCREEN_HEIGHT)
				{
					newRandY = SCREEN_HEIGHT / 2;
				}
				tempEnemy->setEnemyPos(SCREEN_WIDTH + i * 1000, newRandY);

				Bullet* e_bullet = new Bullet();
				tempEnemy->createBullet(render, e_bullet);
			}
		}
	}
}

bool Enemy::enemyAttack(SDL_Renderer* render, SDL_Window* window, Enemy* newEnemy, int numberEnemy,
	const SDL_Rect& spaceshipRect, vector<Bullet*> bullet_list, Mix_Chunk* explosionSound, Explosion explosion, int& markValue, Explosion expMain)
{
	for (int j = 0; j < numberEnemy; j++)
	{
		Enemy* tempEnemy = (newEnemy + j);
		if (tempEnemy)
		{
			tempEnemy->enemyMove();
			tempEnemy->enemyRender(render);
			if (tempEnemy->autoShot(render, SCREEN_WIDTH, SCREEN_HEIGHT, spaceshipRect, explosion))
			{
				for (int exp = 0; exp < NUMBER_FRAME; exp++)
				{
					int exp_x = spaceshipRect.x - explosion.getExpWidth() * 0.5 + 30;
					int exp_y = spaceshipRect.y - explosion.getExpHeight() * 0.5 + 30;

					expMain.setExp(exp);
					expMain.setExpPos(exp_x, exp_y);
					expMain.expRender(render);
					SDL_Delay(25);
					SDL_RenderPresent(render);
				}
				return true;
			}
			
			checkColBulletVsEnemy(bullet_list, tempEnemy, tempEnemy->getEnemyRect(), j, explosionSound, render, explosion, markValue);

			if (checkColSpaceAndEnemy(spaceshipRect, tempEnemy->getEnemyRect()))
			{
				for (int exp = 0; exp < NUMBER_FRAME; exp++)
				{
					int exp_x = spaceshipRect.x - explosion.getExpWidth() * 0.5 + 30;
					int exp_y = spaceshipRect.y - explosion.getExpHeight() * 0.5 + 30;

					expMain.setExp(exp);
					expMain.setExpPos(exp_x, exp_y);
					expMain.expRender(render);
					SDL_Delay(25);
					SDL_RenderPresent(render);
				}
				return true;
			}
		}
	}
	
	return false;
}

void Enemy::checkColBulletVsEnemy(vector<Bullet*> bullet_check, Enemy* colEnemy, const SDL_Rect& enemyRect,
	int reset, Mix_Chunk* explosionSound, SDL_Renderer* render, Explosion explosion, int& markValue)
{
	for (int im = 0; im < bullet_check.size(); im++)
	{
		Bullet* currenBullet = bullet_check.at(im);
		if (currenBullet)
		{
			if (checkColSBAndEnemy(currenBullet->getBulletRect(), enemyRect)) 
			{
				Mix_PlayChannel(-1, explosionSound, 0);
				markValue++;

				for (int exp = 0; exp < NUMBER_FRAME; exp++)
				{
					int exp_x = currenBullet->getBulletRect().x - explosion.getExpWidth() * 0.5 + 30;
					int exp_y = currenBullet->getBulletRect().y - explosion.getExpHeight() * 0.5;
					
					explosion.setExp(exp);
					explosion.setExpPos(exp_x, exp_y);
					explosion.expRender(render);
				}
		
				colEnemy->resetEnemy(SCREEN_WIDTH + reset * 1000);
				currenBullet->setBulletPos(-5, -5);
				currenBullet->removeBullet(im);
			}
		}
	}
}

void Enemy::resetEnemy(int e_reset)
{
	posX = e_reset;
	int newRandY = rand() % 500;
	if (newRandY > SCREEN_HEIGHT)
	{
		newRandY = SCREEN_HEIGHT / 2;
	}
	posY = newRandY;

	for (int n = 0; n < enemyBulletList.size(); n++)
	{
		Bullet* ebullet = enemyBulletList.at(n);
		if (ebullet)
		{
			resetBullet(ebullet);
		}
	}
}

void Enemy::resetBullet(Bullet* bullet_)
{
	bullet_->setBulletPos(posX, posY + enemyTexHeight / 2);
}

void Enemy::resetAllEnemy(Enemy* allEnemy, int numOfEnemy)
{
	for (int i = 0; i < numOfEnemy; i++)
	{
		Enemy* current_enemy = (allEnemy + i);
		current_enemy->resetEnemy(SCREEN_WIDTH + i * 1000);
	}
}

bool Enemy::checkColSpaceAndEnemy(const SDL_Rect& spaceshipRect, const SDL_Rect& enemyRect)
{
	int left_1 = spaceshipRect.x;
	int right_1 = spaceshipRect.x + spaceshipRect.w;
	int top_1 = spaceshipRect.y;
	int bot_1 = spaceshipRect.y + spaceshipRect.h;

	int left_2 = enemyRect.x;
	int right_2 = enemyRect.x + enemyRect.w;
	int top_2 = enemyRect.y;
	int bot_2 = enemyRect.y + enemyRect.h;

	if (right_1 - 30 > left_2 + 30 && right_1 - 30 < left_2 + enemyRect.w * 0.1)
	{
		if ((top_1 > top_2 && top_1 < bot_2) || (bot_1 > top_2 && bot_1 < bot_2))
		{
			return true;
		}
	}
	else if (right_2 > left_1 + 30 && right_2 < right_1)
	{
	    if (top_2 + enemyRect.h * 0.4 > top_1 && top_2 + enemyRect.h * 0.4 < bot_1)
	    {
		     return true;
	    }
	}
	else if (left_1 + 20 > left_2 + enemyRect.w * 0.7 && left_1 + 20 < right_2)
	{
		if (top_2 + enemyRect.h * 0.4 > top_1 && top_2 + enemyRect.h * 0.4 < bot_1 - 20)
		{
			return true;
		}
	}
	else if (left_2 > left_1 && left_2 < right_1)
	{
		if (bot_2 > top_1 + spaceshipRect.h * 0.5 && bot_2 < bot_1)
		{
			return true;
		}
	}
	//
	else if (left_1 > left_2 && left_1 < left_2 + enemyRect.w * 0.7)
	{
		if (top_1 + 30 < bot_2 && top_1 > top_2)
		{
			return true;
		}
	}
	//
	else if (left_1 > left_2 + enemyRect.w * 0.7 && left_1 < right_2)
	{
		if (bot_1 - 20 > top_2 + enemyRect.h * 0.3 && bot_1 < bot_2)
		{
			return true;
		}
	}
	//
	else if (left_1 > left_2 && left_1 < left_2 + enemyRect.w * 0.7)
	{
		if (bot_1 > top_2 && bot_1 < bot_2)
		{
			return true;
		}
	}
	
	return false;
}

bool Enemy::checkColSBAndEnemy(const SDL_Rect& bulletRect, const SDL_Rect& enemyRect)
{
	int left_1 = bulletRect.x;
	int right_1 = bulletRect.x + bulletRect.w;
	int top_1 = bulletRect.y;
	int bot_1 = bulletRect.y + bulletRect.h;

	int left_2 = enemyRect.x;
	int right_2 = enemyRect.x + enemyRect.w;
	int top_2 = enemyRect.y;
	int bot_2 = enemyRect.y + enemyRect.h;

	if (right_1 > left_2 && right_1 < right_2)
	{
		if (top_1 > top_2 && top_1 < bot_2)
		{
			return true;
		}
	}

	return false;
}

SDL_Rect Enemy::getEnemyRect()
{
	SDL_Rect newEnemyRect = { posX, posY, enemyTexWidth, enemyTexHeight };
	return newEnemyRect;
}

int Enemy::getEnemyTexWidth()
{
	return enemyTexWidth;
}

int Enemy::getEnemyTexHeight()
{
	return enemyTexHeight;
}

int Enemy::getEnemyPosX()
{
	return posX;
}

int Enemy::getEnemyPosY()
{
	return posY;
}
