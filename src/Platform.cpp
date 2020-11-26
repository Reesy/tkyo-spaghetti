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
    x += _x; //maybe these can be removed
    y += _y; //unsure just yet
    
    for(int i = 0; i < platformParts.size(); i++)
    {
        platformParts[i].positionRect.x += _x;
        platformParts[i].positionRect.y += _y;

        platformParts[i].collidingRect.x += _x;
        platformParts[i].collidingRect.y += _y;
    }

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
    GameObject beginning_section;

    beginning_section.textureRect = {0, 0, 200, 200};
    beginning_section.positionRect = {x, y, 600, 600};
    beginning_section.collidingRect = {(x + 170), (y + 125), 300, 20};
    platformParts.push_back(beginning_section);
    
   
    
    for (int i = 0; i < midSectionCount; i++ )
    {
        x = x + 300;

        GameObject middleSection;

        middleSection.textureRect = {200, 0, 200, 200};
        middleSection.positionRect = {x, y, 600, 600};
        middleSection.collidingRect =  {(x + 170), (y + 125), 300, 20};
        platformParts.push_back(middleSection);
    };
    x = x + 300;
    
    GameObject end_section;

    end_section.textureRect = {400, 0, 200, 200};
    end_section.positionRect = {x, y, 600, 600};
    end_section.collidingRect =  {(x + 170), (y + 125), 300, 20};
    platformParts.push_back(end_section);
};

std::vector<GameObject> Platform::getBounds()
{   
    return platformParts;
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