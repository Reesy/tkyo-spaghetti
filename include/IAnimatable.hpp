#include <SFML/Graphics.hpp>
#include <IVisible.hpp>

#pragma once
class IAnimatable: public IVisible
{   
    private:
        sf::Texture texture;
        sf::Sprite sprite;
    public: 
        virtual void animate(int speed, int tileOffset){};
        virtual void render(){};
};
