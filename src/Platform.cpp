#include <iostream>
#include <IPlatform.hpp>

Platform::Platform(sf::Texture _texture, int length, int x, int y)
{
    this->texture = _texture;
    this->street_sprite_beginning.setTexture(this->texture);
    this->street_sprite_middle.setTexture(this->texture);
    this->street_sprite_end.setTexture(this->texture);
    
    this->street_sprite_beginning.setTextureRect(sf::IntRect(0, 0, 200, 200));
    this->street_sprite_middle.setTextureRect(sf::IntRect(200, 0, 200, 200));
    this->street_sprite_end.setTextureRect(sf::IntRect(400, 0, 200, 200));

    this->street_sprite_beginning.setScale(3, 3);
    this->street_sprite_middle.setScale(3, 3);
    this->street_sprite_end.setScale(3, 3);

    this->street_sprite_beginning.move(-50, 480);
    this->street_sprite_middle.move(250, 480);
    this->street_sprite_end.move(550, 480);

    this->x = 0;
    this->y = 0;
    this->bounds = sf::RectangleShape(sf::Vector2f(100, 45));
    this->bounds.setFillColor(sf::Color::Transparent);
    this->bounds.setOutlineThickness(1);
    this->bounds.setOutlineColor(sf::Color(255, 255, 255));
    this->bounds.move(55, 80);

    this->createPlatform(3);
};

void Platform::move(int x, int y)
{

    for(int i = 0; i < this->sprites.size(); i++)
    {
        this->sprites[i].move(x, y);
    }
    this->bounds.move(x, y);
};

void Platform::render(sf::RenderWindow &window)
{

    for(int i = 0; i < this->sprites.size(); i++)
    {
        window.draw(sprites[i]);
    }
  
};

void Platform::renderCollider(sf::RenderWindow &window)
{
    window.draw(this->bounds);
}

void Platform::createPlatform(int _length)
{

    this->sprites.push_back(this->street_sprite_beginning);
    this->sprites.push_back(this->street_sprite_middle);
    this->sprites.push_back(this->street_sprite_end);
    // int midSectionCount = 0;

    // if (_length >= 3)
    // {
    //     midSectionCount = _length - 2;
    // }

}

// 1 = 0   []
// 2 = 0   []
// 3 = 1   [-]
// 4 = 2   [--]
