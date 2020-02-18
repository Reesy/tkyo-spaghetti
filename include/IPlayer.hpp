


class Player: public IMovable,
              public IAnimatable
{
    public: 

        void move(int x, int y)
        {
            std::cout << "Currently does nothing" << x << std::endl;
        }

        void animate(int speed, int tileOffset)
        {
            std::cout << "Also does nothing" << std::endl;
        }

        void render()
        {
            std::cout << "Also renders nothing" << std::endl;
        }
};