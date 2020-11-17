#include <SDL.h>
#include <SDL_image.h>
#include <IMovable.hpp>
#include <IAnimatable.hpp>
#include <ICollidable.hpp>
#include <iostream>
#pragma once

class Player: public IMovable,
              public IAnimatable
{
    private:
        int x,y;
        SDL_Texture *texture;
        SDL_Rect spritePosition;

        float animationFrameTimer;
        
    public: 
        SDL_Rect bounds;
        Player(SDL_Texture* _texture);
        void move(int _x, int _y);
        void animate(float _elapsedTime);
        void render(SDL_Renderer *_renderer);
        void renderCollider(SDL_Renderer *_renderer);
        int getX();
        int getY(); 
};
