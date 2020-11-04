// #include <iostream>
// #include <IPlatform.hpp>

// #if __EMSCRIPTEN__
// 	#include <emscripten/emscripten.h>
// 	#include <SDL2/SDL.h>
// #else
// 	#include <SDL.h>
// #endif

// Platform::Platform(SDL_Surface* _texture, int _midSectionCount, int _x, int _y)
// {
//     texture = _texture;
//     x = _x;
//     y = _y;
//     midSectionCount = _midSectionCount;
//     createPlatform();
// };

// void Platform::move(int _x, int _y)
// {

//     for(int i = 0; i < sprites.size(); i++)
//     {
//         sprites[i].move(_x, _y);
//     }

//     for(int i = 0; i < bounds.size(); i++)
//     {
//         bounds[i].move(_x, _y);
//     }

//     x += _x;
//     y += _y;

// };

// void Platform::render(SDL_Window &window)
// {

//     for (int i = 0; i < sprites.size(); i++)
//     {
//         sprites[i].render();
//     }
  
// };

// void Platform::renderCollider(SDL_Window &window)
// {
//     for (int i = 0; i < bounds.size(); i++)
//     {
//         bounds[i].render();
//     }
// }

// void Platform::createPlatform()
// {
    
//     SDL_Surface street_sprite_beginning;
//     SDL_Surface street_sprite_end;

//     street_sprite_beginning.setTexture(*texture);
//     street_sprite_beginning.setTextureRect(sf::IntRect(0, 0, 200, 200));
//     street_sprite_beginning.setScale(3, 3);
//     street_sprite_beginning.move(x, y); 
//     sprites.push_back(street_sprite_beginning);


//     sf::RectangleShape frontBound = sf::RectangleShape(sf::Vector2f(300, 20));
//     frontBound.setFillColor(sf::Color::Transparent);
//     frontBound.setOutlineThickness(1);
//     frontBound.setOutlineColor(sf::Color(255, 255, 255));
//     frontBound.move((x + 170), (y + 125));
//     bounds.push_back(frontBound);


    
//     for (int i = 0; i < midSectionCount; i++ )
//     {
//         x = x + 300; //Platform segments should be placed further along the y segment
//         sf::Sprite middleSection;
//         middleSection.setTexture(*texture);
//         middleSection.setTextureRect(sf::IntRect(200, 0, 200, 200));
//         middleSection.setScale(3, 3);
//         middleSection.move(x, y);
//         sprites.push_back(middleSection);

//         sf::RectangleShape midBounds = sf::RectangleShape(sf::Vector2f(300, 20));
//         midBounds.setFillColor(sf::Color::Transparent);
//         midBounds.setOutlineThickness(1);
//         midBounds.setOutlineColor(sf::Color(255, 255, 255));
//         midBounds.move((x + 170), (y + 125));
//         bounds.push_back(midBounds);

//     }
    
//     x = x + 300;
//     street_sprite_end.setTexture(*texture);
//     street_sprite_end.setTextureRect(sf::IntRect(400, 0, 200, 200));
//     street_sprite_end.setScale(3, 3);
//     street_sprite_end.move(x, y);
//     sprites.push_back(street_sprite_end);

//     sf::RectangleShape endBounds = sf::RectangleShape(sf::Vector2f(300, 20));
//     endBounds.setFillColor(sf::Color::Transparent);
//     endBounds.setOutlineThickness(1);
//     endBounds.setOutlineColor(sf::Color(255, 255, 255));
//     endBounds.move((x + 170), (y + 125));
//     bounds.push_back(endBounds);


// }

// std::vector<SDL_Rect> Platform::getBounds()
// {
//     return bounds;
// };

// int Platform::getX()
// {
//     return x;
// }

// int Platform::getY()
// {
//     return y;
// }

// int Platform::getMidSectionCount()
// {
//     return midSectionCount;
// }