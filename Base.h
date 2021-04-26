#pragma once
#ifndef BASE__H_
#define BASE__H_

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 650;
const int NUMBER_ENEMIES = 10;

using namespace std;

void quitSDL(SDL_Window*& window, SDL_Renderer*& render);

#endif // BASE__H_*/