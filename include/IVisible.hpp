
#pragma once
class IVisible
{   

    private: 
        sf::Texture texture;
        sf::Sprite sprite;
    public: 
        virtual void render(){};
};