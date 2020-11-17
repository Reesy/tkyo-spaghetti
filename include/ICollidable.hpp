#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#pragma once
class ICollidable
{
    SDL_Rect bounds;
    public:
        virtual std::vector<SDL_Rect> getBounds() = 0;
        virtual void renderCollider(SDL_Window &window) = 0;
};