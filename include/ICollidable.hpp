#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <IPlatformRectangles.hpp>
#pragma once
class ICollidable
{
    SDL_Rect bounds;
    public:
        virtual std::vector<PlatformRectangles> getBounds() = 0;
        virtual void renderCollider(SDL_Renderer *_renderer) = 0;
};