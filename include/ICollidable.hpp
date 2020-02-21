#include <SFML/Graphics.hpp>

#pragma once
class ICollidable
{
    sf::RectangleShape bounds;
    public:
        virtual std::vector<sf::RectangleShape> getBounds(){};
        virtual void renderCollider(sf::RenderWindow &window){};
};