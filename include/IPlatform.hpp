// #include <IMovable.hpp>
// #include <ICollidable.hpp>
// #pragma once

// class Platform: public IMovable,
//               public ICollidable
// {
//     private:
//         int x, y, midSectionCount;
//         SDL_Surface* texture;
//         std::vector<SDL_Surface> sprites;
//         std::vector<SDL_Surface> bounds;
//         float animationFrameTimer;
//         void createPlatform();
//     public: 
//         Platform(SDL_Surface* _texture, int _length, int x, int y);
//         int getX();
//         int getY();
//         int getMidSectionCount();
//         void move(int x, int y);
//         void render(SDL_Window &window);
//         void renderCollider(SDL_Window &window);
//         std::vector<SDL_Rect> getBounds();
// };
