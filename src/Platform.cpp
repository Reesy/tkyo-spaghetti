#include <iostream>
#include <IPlatform.hpp>

Platform::Platform(sf::Texture _texture, int length, int x, int y)
{
    this->texture = _texture;
    this->x = 0;
    this->y = 0;
    this->bounds = sf::RectangleShape(sf::Vector2f(100, 45));
    this->bounds.setFillColor(sf::Color::Transparent);
    this->bounds.setOutlineThickness(1);
    this->bounds.setOutlineColor(sf::Color(255, 255, 255));
    this->bounds.move(55, 80);
    this->createPlatform(length, x, y);
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

void Platform::createPlatform(int _midSectionlength, int x, int y)
{
    
    sf::Sprite street_sprite_beginning;
    sf::Sprite street_sprite_end;

    street_sprite_beginning.setTexture(this->texture);
    street_sprite_beginning.setTextureRect(sf::IntRect(0, 0, 200, 200));
    street_sprite_beginning.setScale(3, 3);
    street_sprite_beginning.move(x, y); //-50 480 

    this->sprites.push_back(street_sprite_beginning);
    
    for (int i = 0; i < _midSectionlength; i++ )
    {
        x = x + 300; //Platform segments should be placed further along the y segment
        sf::Sprite middleSection;
        middleSection.setTexture(this->texture);
        middleSection.setTextureRect(sf::IntRect(200, 0, 200, 200));
        middleSection.setScale(3, 3);
        middleSection.move(x, y);
        this->sprites.push_back(middleSection);
    }
    
    x = x + 300;
    street_sprite_end.setTexture(this->texture);
    street_sprite_end.setTextureRect(sf::IntRect(400, 0, 200, 200));
    street_sprite_end.setScale(3, 3);
    street_sprite_end.move(x, y);
   
    this->sprites.push_back(street_sprite_end);

}


