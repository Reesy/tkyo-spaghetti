#include <IMovable.hpp>
#include <IAnimatable.hpp>
#pragma once

class Player: public IMovable,
              public IAnimatable
{
    private:
        int x,y;
        sf::Texture texture;
        sf::Sprite sprite;
        float animationFrameTimer;
    
    public: 
        Player(sf::Texture _texture);
        void move(int x, int y);
        void animate(float elapsedTime);
        void render(sf::RenderWindow &window);
};
