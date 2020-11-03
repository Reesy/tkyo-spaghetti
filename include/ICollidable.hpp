
#pragma once
class ICollidable
{
    sf::RectangleShape bounds;
    public:
        virtual std::vector<sf::RectangleShape> getBounds() = 0;
        virtual void renderCollider(sf::RenderWindow &window){};
};