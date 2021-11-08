#include "Base.h"
#include "Background.h"
#include "Spaceship.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Text.h"
#include "Life.h"

bool initSDL(SDL_Window*& window, SDL_Renderer*& render);

int main(int argc, char* argv[])
{
    SDL_Window* window = NULL;
    SDL_Renderer* render = NULL;
    SDL_Event events;

    if (!initSDL(window, render)) return 0;
    else
    {
        bool quit = false;

        Background background;

        Background menu[5];

        Spaceship spaceship;

        Bullet bullet;

        Enemy enemy;

        Explosion explosion;

        Explosion expMain;

        Enemy* initEnemy = new Enemy[NUMBER_ENEMIES];

        Life life;

        Mix_Chunk* laserSound = Mix_LoadWAV("laser_gun.wav");

        Mix_Chunk* explosionSound = Mix_LoadWAV("explosion_sound.wav");
        
        Mix_Music* galaxySound = Mix_LoadMUS("galaxy_sound.wav");

        TTF_Font* font = TTF_OpenFont("inside_font.ttf", 20);

        Text time;
        time.setColorWithType(Text::WHITE);

        Text mark;
        mark.setColorWithType(Text::WHITE);
        int markValue = 0;

        int scrolling = 0;

        int numberLife = 3;

        Mix_PlayMusic(galaxySound, -1);

        if (!background.loadBackgroundImg("black_galaxy.png", render))
        {
            cout << "Khong tai duoc background";
            return 0;
        }
        if (!spaceship.loadSpaceshipImg("spaceship_(1).png", render))
        {
            cout << "Khong tai duoc anh spaceship";
            return 0;
        }
        if (!explosion.loadExpImg("explosion_(1).png", render))
        {
            cout << "Khong tai duoc anh explosion";
            return 0;
        }

        menu[0].loadBackgroundImg("menu_galaxy.png", render);
        menu[1].loadBackgroundImg("play.png", render);
        menu[2].loadBackgroundImg("exit.png", render);
        menu[3].loadBackgroundImg("win.png", render);
        menu[4].loadBackgroundImg("failed.png", render);

        expMain.loadExpImg("bum.png", render);

        expMain.setClip();

        explosion.setClip();

        enemy.createEnemy(render, initEnemy, NUMBER_ENEMIES);

        life.initLife(render);
        
        bool is_quit = true;

        while (!quit)
        {
            menu[0].renderBackground(0, 0, render);
            menu[1].renderBackground(500, 350, render);
            menu[2].renderBackground(500, 500, render);
            SDL_RenderPresent(render);
            while (SDL_PollEvent(&events) != 0 && is_quit == true)
            {
                if (events.type == SDL_KEYDOWN)
                {
                    switch (events.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                    {
                        quitSDL(window, render);
                        return 0;
                    }
                        break;
                    case SDLK_KP_ENTER:
                        quit = true;
                        break;
                    default:
                        break;
                    }
                }
            }
        }

        quit = false;
        
        while (!quit)
        {
            while (SDL_PollEvent(&events) != 0)
            {
                if (events.type == SDL_QUIT)
                {
                    quit = true;
                }
                
                spaceship.handleInput(events, render);
                bullet.handleInputBullet(events, render, laserSound,
                    spaceship.getPosX() + spaceship.getSpaceshipWidth() - 20, spaceship.getPosY() + spaceship.getSpaceshipHeight() / 2);
            }

            spaceship.spaceshipMove();

            scrolling -= 2;
            if (scrolling < -background.getBackgroundWidth())
            {
                scrolling = 0;
            }
            background.renderBackground(scrolling, 0, render);
            background.renderBackground(scrolling + background.getBackgroundWidth(), 0, render);

            bullet.handleBullet(render);

            spaceship.spaceshipRender(render);

            life.showLife(render);
            
            string texTime = "Time Survive: ";
            Uint32 timeValue = SDL_GetTicks() / 1000;
            string currentTime = to_string(timeValue);
            texTime += currentTime;
            time.setText(texTime);
            time.loadFromRenderTex(font, render);
            time.setTexPos(SCREEN_WIDTH - 200, 10);
            time.texRender(render);
            
            string texMark = "Mark: ";
            string currentMark = to_string(markValue);
            texMark += currentMark;
            mark.setText(texMark);
            mark.loadFromRenderTex(font, render);
            mark.setTexPos(SCREEN_WIDTH / 2 - 50, 10);
            mark.texRender(render);

            if (markValue >= 50 && timeValue >= 60)
            {
                menu[3].renderBackground(0, 0, render);
                SDL_RenderPresent(render);
                SDL_Delay(3000);
                quitSDL(window, render);
                return 0;
            }

            if (enemy.enemyAttack(render, window, initEnemy, NUMBER_ENEMIES, spaceship.getSpaceshipRect(),
                 bullet.getBulletList(), explosionSound, explosion, markValue, expMain))
            {
                Mix_PlayChannel(-1, explosionSound, 0);
                numberLife--;
                if (numberLife > 0)
                {
                    spaceship.setSpaceshipPos(150, 250);
                    enemy.resetAllEnemy(initEnemy, NUMBER_ENEMIES);
                    life.decreaseLife();
                    life.lifeRender(render);
                    SDL_Delay(500);
                    bullet.getBulletList().clear();
                }
                else
                {
                    menu[4].renderBackground(0, 0, render);
                    SDL_RenderPresent(render);
                    SDL_Delay(3000);
                    quitSDL(window, render);
                    return 0;
                }
            }

            SDL_RenderPresent(render);
        
        }

        delete[] initEnemy;
    }

    quitSDL(window, render);

    return 0;
}

bool initSDL(SDL_Window*& window, SDL_Renderer*& render)
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        cout << "Khong the khoi tao SDL: " << SDL_GetError();
        success = false;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            cout << "Khong cai dat duoc chat luong";
        }
        window = SDL_CreateWindow("Space Impact", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED
            , SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            cout << "Khong khoi tao duoc cua so: " << SDL_GetError();
            success = false;
        }
        else
        {
            render = SDL_CreateRenderer(window, -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (render == NULL)
            {
                cout << "Khong the khoi tao render: " << SDL_GetError();
                success = false;
            }
            else
            {
                int Img = IMG_INIT_PNG;
                if (!(IMG_Init(Img) & Img))
                {
                    cout << "Khong the khoi tao IMG: " << IMG_GetError();
                    success = false;
                }
                if (TTF_Init() < 0)
                {
                    cout << "Khong the khoi tao TTF: " << TTF_GetError();
                    success = false;
                }
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    cout << "Khong the khoi tao Mixer: " << Mix_GetError();
                    success = false;
                }
            }
        }
    }
    return success;
}
