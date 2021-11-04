#include <SDL.h>
#include <SDL_image.h>
#include <IVisible.hpp>

#pragma once

class Score: public IVisible {
public:
    Score();
    ~Score();
    void render(SDL_Renderer *renderer);
    void setScore(int score);
    
private:
    int score;
};