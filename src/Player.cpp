#include <IPlayer.hpp>

Player::Player(SDL_Texture* _texture)
{
    this->texture = _texture;
    this->textureRect = {0, 0, 110, 68};
    this->positionRect = {55, 60, 110, 68};
    this->collidingRect = {55, 80, 100, 45};
    // this->bounds = sf::RectangleShape(sf::Vector2f(100, 45));
    // this->bounds.setFillColor(sf::Color::Transparent);
    // this->bounds.setOutlineThickness(1);
    // this->bounds.setOutlineColor(sf::Color(255, 255, 255));
    // this->bounds.move(55, 80);
};

void Player::move(int _x, int _y)
{
    this->positionRect.x += _x;
    this->positionRect.y += _y;
    this->collidingRect.x += _x;
    this->collidingRect.y += _y;
    // this->sprite.move(_x, _y);
    // this->bounds.move(_x, _y);
};

void Player::animate(double _elapsedTime)
{ 
    
    this->animationClock += _elapsedTime; //This works like a stopwatch, the time since the last frame is accumulated (in MS)
   
    //Every 100ms progress the animation frame. Then reset the stopwatch (animationClock)
    if ((this->animationClock) > 100)
    {
        this->frame++;
        this->animationClock = 0.0;
    }
    \
    //439x408  4 x 6    109.75x 68
    if (this->frame == 0)
    {
        this->textureRect = {0, 0, 110, 68};
    }
    if (this->frame == 1)
    {
        this->textureRect = {110, 0, 110, 68};
    } 
    else if (this->frame == 2)
    {
        this->textureRect = {220, 0, 110, 68};
    }
    else if (this->frame == 3)
    {
        this->textureRect = {330, 0, 110, 68};
    }
    else if (this->frame == 4)
    {
        this->textureRect = {0, 68, 110, 68};
    }
    else if (this->frame == 5)
    {
        this->textureRect = {110, 68, 110, 68};
    }
    else if (this->frame == 6)
    {
        this->textureRect = {220, 68, 110, 68};
    }
    else if (this->frame == 7)
    {
        this->textureRect = {330, 68, 110, 68};
    }
    else if (this->frame == 8)
    {
        this->textureRect = {0, 136, 110, 68};
    }
    else if (this->frame == 9)
    {
        this->textureRect = {110, 136, 110, 68};
    }
    else if (this->frame == 10)
    {
        this->textureRect = {220, 136, 110, 68};
    }
    else if (this->frame == 11)
    {
        this->textureRect = {330, 136, 110, 68};
    }
    else if (this->frame == 12)
    {
        this->textureRect = {0, 204, 110, 68};
    }
    else if (this->frame == 13)
    {
        this->textureRect = {110, 204, 110, 68};
    }
    else if (this->frame == 14)
    {
        this->textureRect = {220, 204, 110, 68};
    }
    else if (this->frame == 15)
    {
        this->textureRect = {330, 204, 110, 68};
    }
    else if (this->frame == 16)
    {
        this->textureRect = {0, 272, 110, 68};
    }
    else if (this->frame == 17)
    {
        this->textureRect = {110, 272, 110, 68};
    }
    else if (this->frame == 18)
    {
        this->textureRect = {220, 272, 110, 68};
    }
    else if (this->frame == 19)
    {
        this->textureRect = {330, 272, 110, 68};
    }
    else if (this->frame == 20)
    {
        this->textureRect = {0, 340, 110, 68};
    }
    else if (this->frame == 21)
    {
        this->textureRect = {110, 340, 110, 68};
    }
    else if (this->frame >= 22)
    {
        this->textureRect = {220, 340, 110, 68};
        this->frame = 0;
        return;
    }
    return;
};

void Player::render(SDL_Renderer *_renderer)
{
    SDL_RenderCopy(_renderer, this->texture, &this->textureRect, &this->positionRect);
};

void Player::renderCollider(SDL_Renderer *_renderer)
{
    SDL_SetRenderDrawColor( _renderer, 0x00, 0xFF, 0x00, 0xFF );		
    SDL_RenderDrawRect( _renderer, &this->collidingRect);
    return;
}

int Player::getX()
{
    return this->positionRect.x;
}

int Player::getY()
{
    return this->positionRect.y;
}