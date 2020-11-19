#include <IPlatform.hpp>


Platform::Platform(SDL_Texture* _texture, int _midSectionCount, int _x, int _y)
{
    texture = _texture;
    midSectionCount = _midSectionCount;
    x = _x;
    y = _y;
    createPlatform();
};

void Platform::move(int _x, int _y)
{

    // for(int i = 0; i < sprites.size(); i++)
    // {
    //     sprites[i].move(_x, _y);
    // }

    // for(int i = 0; i < bounds.size(); i++)
    // {
    //     bounds[i].move(_x, _y);
    // }

    // x += _x;
    // y += _y;

};

void Platform::render(SDL_Renderer *_renderer)
{
    for (int i = 0; i < this->platformParts.size(); i++)
    {
        SDL_RenderCopy(_renderer,
                       this->texture, 
                       &platformParts[i].textureRect, 
                       &platformParts[i].positionRect);
    };
};

void Platform::renderCollider(SDL_Renderer *_renderer)
{   
    for (int i = 0; i < this->platformParts.size(); i++)
    {
        SDL_SetRenderDrawColor( _renderer, 0x00, 0xFF, 0x00, 0xFF );		
        SDL_RenderDrawRect( _renderer, &platformParts[i].collidingRect);
    };
}

void Platform::createPlatform()
{
    std::cout << "create platform called" << std::endl;
    PlatformRectangles beginning_section;

    beginning_section.textureRect = {0, 0, 200, 200};
    beginning_section.positionRect = {x, y, 600, 600};
    beginning_section.collidingRect = {(x + 170), (y + 125), 300, 20};
    platformParts.push_back(beginning_section);
    
    x = x + 300;
    
    for (int i = 0; i < midSectionCount; i++ )
    {
        PlatformRectangles middleSection;

        middleSection.textureRect = {200, 0, 200, 200};
        middleSection.positionRect = {x, y, 600, 600};
        middleSection.collidingRect =  {(x + 170), (y + 125), 300, 20};
        platformParts.push_back(middleSection);
    };
    
    PlatformRectangles end_section;

    end_section.textureRect = {400, 0, 200, 200};
    end_section.positionRect = {x, y, 600, 600};
    end_section.collidingRect =  {(x + 170), (y + 125), 300, 20};
    platformParts.push_back(end_section);
};

std::vector<SDL_Rect> Platform::getBounds()
{   
    std::vector <SDL_Rect> randomVector;
    return randomVector;
};

int Platform::getX()
{
    return x;
}

int Platform::getY()
{
    return y;
}

int Platform::getMidSectionCount()
{
    return midSectionCount;
}