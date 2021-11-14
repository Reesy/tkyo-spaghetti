#include <IScore.hpp>
#include <iostream>

Score::Score(SDL_Texture *_texture, 
                int _x, 
                int _y, 
                int _width, 
                int _height)
{
    this->x = _x;
    this->y = _y;
    this->width = _width;
    this->height = _height;
    this->placementRect = new SDL_Rect{_x, _y, _width, _height};
    this->texture = _texture;
    this->scoreString = "0";
    digitRects[0] = {0, 0, 7, 10};
    digitRects[1] = {7, 0, 7, 10};
    digitRects[2] = {14, 0, 7, 10};
    digitRects[3] = {21, 0, 7, 10};
    digitRects[4] = {28, 0, 7, 10};
    digitRects[5] = {35, 0, 7, 10};
    digitRects[6] = {42, 0, 7, 10};
    digitRects[7] = {49, 0, 7, 10};
    digitRects[8] = {56, 0, 7, 10};
    digitRects[9] = {63, 0, 7, 10};
};

Score::~Score()
{

};

void Score::update(int _score)
{
    this->score = _score;
    this->scoreString = std::to_string(_score);
};

void Score::render(SDL_Renderer *_renderer)
{
    for (int i = 0; i < this->scoreString.length(); i++)
    {
        placementRect->x = placementRect->x + placementRect->w;
        SDL_RenderCopy(_renderer, this->texture, &digitRects[scoreString[i] - 48], placementRect);
    };
    placementRect->x = this->x;
};

void Score::move(int _x, int _y)
{
    std::cout << "Not yet implemented" << std::endl;
};