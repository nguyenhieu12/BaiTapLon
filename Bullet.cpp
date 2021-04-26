#include "Bullet.h"

Bullet::Bullet()
{
	bulletImg = NULL;
	posX = 0;
	posY = 0;
    bulletTexWidth = 0;
    bulletTexHeight = 0;
    bulletVel = 15;
	isShot = false;
}

Bullet::~Bullet()
{
	freeBullet();
}

bool Bullet::loadBulletImg(string bulletPath, SDL_Renderer* render)
{
	freeBullet();

    SDL_Texture* newBulletTexture = NULL;

    SDL_Surface* newBulletSurface = IMG_Load(bulletPath.c_str());

    if (newBulletSurface == NULL)
    {
        cout << "Khong the tai anh bullet: " << IMG_GetError();
    }
    else
    {
        newBulletTexture = SDL_CreateTextureFromSurface(render, newBulletSurface);
        if (newBulletTexture == NULL)
        {
            cout << "Khong the tao BulletTexture: " << SDL_GetError();
        }
        else
        {
            bulletTexWidth = newBulletSurface->w;
            bulletTexHeight = newBulletSurface->h;
        }
        SDL_FreeSurface(newBulletSurface);
    }

    bulletImg = newBulletTexture;

    return bulletImg != NULL;
}

void Bullet::freeBullet()
{
    if (bulletImg != NULL)
    {
        SDL_DestroyTexture(bulletImg);
        bulletImg = 0;
        posX = 0;
        posY = 0;
        bulletTexWidth = 0;
        bulletTexHeight = 0;
        isShot = false;
    }
}

void Bullet::bulletMove(int limX, int limY)
{
    posX += bulletVel;
    if (posX + bulletTexWidth > limX)
    {
        isShot = false;
    }
}

void Bullet::bulletMoveRightToLeft()
{
    posX -= bulletVel;
    if (posX < 0)
    {
        isShot = false;
    }
}

void Bullet::bulletRender(SDL_Renderer* render)
{
    SDL_Rect bulletQuad = { posX, posY, bulletTexWidth, bulletTexHeight };
    SDL_RenderCopy(render, bulletImg, NULL, &bulletQuad);
}

void Bullet::setBulletPos(int PosX, int PosY)
{
    posX = PosX;
    posY = PosY;
}

void Bullet::handleInputBullet(SDL_Event event, SDL_Renderer* render, Mix_Chunk* laserSound, int PosX, int PosY)
{
   
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        Bullet* newBullet = new Bullet();
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            Mix_PlayChannel(-1, laserSound, 0);
            newBullet->loadBulletImg("red_laser.png", render);
            newBullet->setBulletPos(PosX, PosY);
            newBullet->setIsShot(true);
        }
        else if (event.button.button == SDL_BUTTON_RIGHT)
        {
            Mix_PlayChannel(-1, laserSound, 0);
            newBullet->loadBulletImg("green_laser.png", render);
            newBullet->setBulletPos(PosX, PosY);
            newBullet->setIsShot(true);
        }
        bulletList.push_back(newBullet);
    }
}

void Bullet::handleBullet(SDL_Renderer* render)
{
    for (int i = 0; i < bulletList.size(); i++)
    {
        Bullet* tempBullet = bulletList.at(i);
        if (tempBullet != NULL)
        {
            if (tempBullet->getIsShot() == true)
            {
                tempBullet->bulletMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                tempBullet->bulletRender(render);
            }
            else
            {
                bulletList.erase(bulletList.begin() + i);
                if (tempBullet != NULL)
                {
                    delete tempBullet;
                    tempBullet = NULL;
                }
            }
        }
    }
}

bool Bullet::checkColSpaceAndEnemyBullet(const SDL_Rect& spaceshipRect, const SDL_Rect& enemyBulletRect)
{
    int left_1 = spaceshipRect.x;
    int right_1 = spaceshipRect.x + spaceshipRect.w;
    int top_1 = spaceshipRect.y;
    int bot_1 = spaceshipRect.y + spaceshipRect.h;

    int left_2 = enemyBulletRect.x;
    int right_2 = enemyBulletRect.x + enemyBulletRect.w;
    int top_2 = enemyBulletRect.y;
    int bot_2 = enemyBulletRect.y + enemyBulletRect.h;

    if (left_2 > left_1 && left_2 < right_1 - 10)
    {
        if (top_2 >= top_1 + spaceshipRect.h * 0.45 && top_2 <= top_1 + spaceshipRect.h * 0.65)
        {
            return true;
        }
        else if ((top_2 > top_1 && top_2 < top_1 + spaceshipRect.h * 0.45) || (top_2 > top_1 + spaceshipRect.h * 0.7 && top_2 < bot_1 - 20))
        {
            if (left_2 > left_1 && left_2 < left_1 + spaceshipRect.w * 0.5)
            {
                return true;
            }
        }
        else if ((top_2 < top_1 + spaceshipRect.h * 0.1 && top_2 > top_1) || (bot_2 > top_1 + spaceshipRect.h * 0.9 && bot_2 < bot_1 - 20))
        {
            if (left_2 > left_1 && left_2 < left_1 + spaceshipRect.w * 0.08)
            {
                return true;
            }
        }
    }
    
    return false;
}

void Bullet::removeBullet(const int pos)
{
    //for (int k = 0; k < bulletList.size(); k++)
    //{
        if (bulletList.size() > 0 && pos < bulletList.size())
        {
            Bullet* nowBullet = bulletList.at(pos);
            bulletList.erase(bulletList.begin() + pos);
            if (nowBullet)
            {
                delete nowBullet;
                nowBullet = NULL;
            }
        }
    //}
}

SDL_Rect Bullet::getBulletRect()
{
    SDL_Rect newBulletRect = { posX, posY, bulletTexWidth, bulletTexHeight };
    return newBulletRect;
}

int Bullet::getPosX()
{
    return posX;
}

int Bullet::getPosY()
{
    return posY;
}

int Bullet::getBulletWidth()
{
    return bulletTexWidth;
}

int Bullet::getBulletHeight()
{
    return bulletTexHeight;
}





