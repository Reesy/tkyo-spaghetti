#include <SFML/Graphics.hpp>

#pragma once
class ICollidable
{
    sf::RectangleShape bounds;
    public:
        virtual void renderCollider(sf::RenderWindow &window){};
};