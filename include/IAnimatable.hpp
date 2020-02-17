class IAnimatable: public IVisible
{   
    private:
        sf::Texture texture;
    public: 
        virtual void animate(int speed, int tileOffset) = 0;
        virtual void render() = 0;
};
