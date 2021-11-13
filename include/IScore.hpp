#include <SDL.h>
#include <SDL_image.h>
#include <IVisible.hpp>
#include <IMovable.hpp>
#include <iostream>

#pragma once

class Score: public IVisible,
            public IMovable 
{
public:
    Score(SDL_Texture* _texture, 
            int x, 
            int y,
            int width,
            int height);
    ~Score();
    void render(SDL_Renderer *renderer);
    void update(int score);
    void move(int x, int y);
    
private:
    int score, x, y, width, height;
    SDL_Rect *placementRect;
    SDL_Rect digitRects[10];
    std::string scoreString;
    SDL_Texture *texture;
};