#include <IMovable.hpp>
#include <IAnimatable.hpp>

#pragma once
class Player: public IMovable,
              public IAnimatable
{
    public: 
        void move(int x, int y);
        void animate(int speed, int tileOffset);
        void render();
};
