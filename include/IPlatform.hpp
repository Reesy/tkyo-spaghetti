#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <IMovable.hpp>
#include <ICollidable.hpp>
#include <IPlatformRectangles.hpp>
#pragma once


class Platform: public IMovable,
              public ICollidable
{
    private:
        int x, y, midSectionCount;
        SDL_Texture* texture;
        std::vector<PlatformRectangles> platformParts;
        std::vector<SDL_Rect> bounds;
        float animationFrameTimer;
        void createPlatform();
    public: 
        Platform(SDL_Texture* _texture, int _length, int x, int y);
        int getX();
        int getY();
        int getMidSectionCount();
        void move(int x, int y);
        void render(SDL_Renderer *_renderer);
        void renderCollider(SDL_Renderer *_renderer);
        std::vector<PlatformRectangles> getBounds();
};
