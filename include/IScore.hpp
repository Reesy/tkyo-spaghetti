#include <SDL.h>
#include <SDL_image.h>
#include <IVisible.hpp>
#include <IMovable.hpp>

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
    void update(float score);
    void move(int x, int y);
    
private:
    SDL_Rect *placementRect;
    float score;
    SDL_Texture *texture;
};