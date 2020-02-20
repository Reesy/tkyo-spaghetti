#include <iostream>
#include <IPlayer.hpp>

Player::Player(sf::Texture _texture)
{
    this->texture = _texture;
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(0, 0, 200, 200));
    this->x = 0;
    this->y = 0;
};

void Player::move(int x, int y)
{
    this->sprite.move(x, y);
};

void Player::animate(float elapsedTime)
{
    this->sprite.setTextureRect(sf::IntRect(0, 0, 200, 200));
    this->animationFrameTimer += elapsedTime * 7;

    if (this->animationFrameTimer > 1 && this->animationFrameTimer < 2)
    {
        this->sprite.setTextureRect(sf::IntRect(200, 0, 200, 200));
    } 
    else if (this->animationFrameTimer > 2 && this->animationFrameTimer < 3)
    {
        this->sprite.setTextureRect(sf::IntRect(400, 0, 200, 200));
    }
    else if (this->animationFrameTimer > 3 && this->animationFrameTimer < 4)
    {
        this->sprite.setTextureRect(sf::IntRect(600, 0, 200, 200));
    }
    else if (this->animationFrameTimer > 4 && this->animationFrameTimer < 5)
    {
        this->sprite.setTextureRect(sf::IntRect(800, 0, 200, 200));
    }
    else if (this->animationFrameTimer > 5 && this->animationFrameTimer < 6)
    {
        this->sprite.setTextureRect(sf::IntRect(1000, 0, 200, 200));
    }
    else if (this->animationFrameTimer > 6 && this->animationFrameTimer < 7)
    {
        this->sprite.setTextureRect(sf::IntRect(1200, 0, 200, 200));
    }
    else if (this->animationFrameTimer > 7 && this->animationFrameTimer < 8)
    {
        this->sprite.setTextureRect(sf::IntRect(1400, 0, 200, 200));
    }
    else if (this->animationFrameTimer > 8 && this->animationFrameTimer < 9)
    {
        this->sprite.setTextureRect(sf::IntRect(1600, 0, 200, 200));
    }
    else if (this->animationFrameTimer > 9 && this->animationFrameTimer < 10)
    {
        this->sprite.setTextureRect(sf::IntRect(1800, 0, 200, 200));
    }
    else if (this->animationFrameTimer > 10 && this->animationFrameTimer < 11)
    {
        this->sprite.setTextureRect(sf::IntRect(2000, 0, 200, 200));
    }
    else if (this->animationFrameTimer > 11 && this->animationFrameTimer < 12)
    {
        this->sprite.setTextureRect(sf::IntRect(2200, 0, 200, 200));
    }
    else if (this->animationFrameTimer > 12 && this->animationFrameTimer < 13)
    {
        this->sprite.setTextureRect(sf::IntRect(2400, 0, 200, 200));
    }
    else if (this->animationFrameTimer > 13 && this->animationFrameTimer < 14)
    {
        this->sprite.setTextureRect(sf::IntRect(2600, 0, 200, 200));
    }
    else if (this->animationFrameTimer > 14 && this->animationFrameTimer < 15)
    {
        this->sprite.setTextureRect(sf::IntRect(2800, 0, 200, 200));
    }
    else if (this->animationFrameTimer > 15 && this->animationFrameTimer < 16)
    {
        this->sprite.setTextureRect(sf::IntRect(3000, 0, 200, 200));
    }
    else if (this->animationFrameTimer > 16 && this->animationFrameTimer < 17)
    {
        this->sprite.setTextureRect(sf::IntRect(3200, 0, 200, 200));
    }
    else if (this->animationFrameTimer > 17 && this->animationFrameTimer < 18)
    {
        this->sprite.setTextureRect(sf::IntRect(3400, 0, 200, 200));
    }
    else if (this->animationFrameTimer > 18 && this->animationFrameTimer < 19)
    {
        this->sprite.setTextureRect(sf::IntRect(3600, 0, 200, 200));
    }
    else if (this->animationFrameTimer > 19 && this->animationFrameTimer < 20)
    {
        this->sprite.setTextureRect(sf::IntRect(3800, 0, 200, 200));
    }
    else if (this->animationFrameTimer > 20 && this->animationFrameTimer < 21)
    {
        this->sprite.setTextureRect(sf::IntRect(4000, 0, 200, 200));
    }
    else if (this->animationFrameTimer > 21 && this->animationFrameTimer < 22)
    {
        this->sprite.setTextureRect(sf::IntRect(4200, 0, 200, 200));
    }
    else if (this->animationFrameTimer > 22 && this->animationFrameTimer < 23)
    {
        this->sprite.setTextureRect(sf::IntRect(4600, 0, 200, 200));
        this->animationFrameTimer = 0;
    }
};

void Player::render(sf::RenderWindow &window)
{
    window.draw(this->sprite);
};