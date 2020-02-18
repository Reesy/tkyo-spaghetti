#include <iostream>
#include <IPlayer.hpp>

void Player::move(int x, int y)
{
    std::cout << "Currently does nothing" << x << std::endl;
};

void Player::animate(int speed, int tileOffset)
{
     std::cout << "Also does nothing" << std::endl;
};

void Player::render()
{
    std::cout << "Also renders nothing" << std::endl;
};