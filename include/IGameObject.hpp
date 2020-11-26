#include <SDL.h>
#include <SDL_image.h>
#pragma once

struct GameObject
{
    SDL_Rect textureRect;    //This will represent which part of the platform texture to render
    SDL_Rect positionRect;   //This will represent the position of the platform
    SDL_Rect collidingRect;  //This will represent the colliding bounds of the platform
};