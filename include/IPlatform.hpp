#include <IMovable.hpp>
#include <ICollidable.hpp>
#pragma once

class Platform: public IMovable,
              public ICollidable
{
    private:
        int x,y;
        sf::Texture texture;
        sf::Sprite street_sprite_beginning;
        sf::Sprite street_sprite_middle;
        sf::Sprite street_sprite_end;
        std::vector<sf::Sprite> sprites;
        float animationFrameTimer;
        void createPlatform(int _length);
    public: 
        sf::RectangleShape bounds;
        Platform(sf::Texture _texture, int _length, int x, int y);
        void move(int x, int y);
        void render(sf::RenderWindow &window);
        void renderCollider(sf::RenderWindow &window);
};
