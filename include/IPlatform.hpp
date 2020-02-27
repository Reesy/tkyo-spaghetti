#include <IMovable.hpp>
#include <ICollidable.hpp>
#pragma once

class Platform: public IMovable,
              public ICollidable
{
    private:
        int x, y, midSectionCount;
        sf::Texture* texture;
        std::vector<sf::Sprite> sprites;
        std::vector<sf::RectangleShape> bounds;
        float animationFrameTimer;
        void createPlatform();
    public: 
        Platform(sf::Texture* _texture, int _length, int x, int y);
        int getX();
        int getY();
        int getMidSectionCount();
        void move(int x, int y);
        void render(sf::RenderWindow &window);
        void renderCollider(sf::RenderWindow &window);
        std::vector<sf::RectangleShape> getBounds();
};
