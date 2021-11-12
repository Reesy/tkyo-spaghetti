#include <IScore.hpp>
#include <iostream>

Score::Score(SDL_Texture *_texture, 
                int _x, 
                int _y, 
                int _width, 
                int _height)
{
  //  this->placementRect = {_x, _y, _width, _height};
    this->placementRect = new SDL_Rect{_x, _y, _width, _height};
    // this->placementRect->x = _x;
    // this->placementRect->y = _y;
    // this->placementRect->w = _width;
    // this->placementRect->h = _height;
    this->texture = _texture;
};

Score::~Score()
{

};

void Score::render(SDL_Renderer *_renderer)
{
    SDL_RenderCopy(_renderer, this->texture, NULL, placementRect);
};

void Score::move(int _x, int _y)
{
    std::cout << "Not yet implemented" << std::endl;
};