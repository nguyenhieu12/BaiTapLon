#include "Base.h"

void quitSDL(SDL_Window*& window, SDL_Renderer*& render)
{
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_DestroyRenderer(render);
    render = NULL;

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}

