static void poleDancerAnimate(float elapsedTime)
{
    pole_dancer_sprite.setTexture(pole_dancer_texture);
    pole_dancer_sprite.setTextureRect(sf::IntRect(0, 0, 1000, 1000));
    pole_dancer_accumulator += elapsedTime * animate_speed;

    if (pole_dancer_accumulator > 1 && pole_dancer_accumulator < 2)
    {
        pole_dancer_sprite.setTextureRect(sf::IntRect(0, 0, 1000, 1000));
    } 
    else if (pole_dancer_accumulator > 2 && pole_dancer_accumulator < 3)
    {
        pole_dancer_sprite.setTextureRect(sf::IntRect(1000, 0, 1000, 1000));
    }
    else if (pole_dancer_accumulator > 3 && pole_dancer_accumulator < 4)
    {
        pole_dancer_sprite.setTextureRect(sf::IntRect(2000, 0, 1000, 1000));
    }
    else if (pole_dancer_accumulator > 4 && pole_dancer_accumulator < 5)
    {
        pole_dancer_sprite.setTextureRect(sf::IntRect(3000, 0, 1000, 1000));
    }
    else if (pole_dancer_accumulator > 5)
    {
        pole_dancer_sprite.setTextureRect(sf::IntRect(4000, 0, 1000, 1000));
        pole_dancer_accumulator = 0;
    }
};

static void stripperAnimate(float elapsedTime)
{
    stripper_sprite.setTexture(stripper_texture);
    stripper_accumulator += elapsedTime * animate_speed;
    stripper_sprite.setTextureRect(sf::IntRect(0, 0, 1000, 1000));

    if (stripper_accumulator > 1 && stripper_accumulator < 2)
    {
        stripper_sprite.setTextureRect(sf::IntRect(1000, 0, 1000, 1000));
    } 
    else if (stripper_accumulator > 2 && stripper_accumulator < 3)
    {
        stripper_sprite.setTextureRect(sf::IntRect(2000, 0, 1000, 1000));
    }
    else if (stripper_accumulator > 3 && stripper_accumulator < 4)
    {
        stripper_sprite.setTextureRect(sf::IntRect(3000, 0, 1000, 1000));
    }
    else if (stripper_accumulator > 4 && stripper_accumulator < 5)
    {
        stripper_sprite.setTextureRect(sf::IntRect(4000, 0, 1000, 1000));
    }
    else if (stripper_accumulator > 5)
    {
        stripper_sprite.setTextureRect(sf::IntRect(0, 0, 1000, 1000));
        stripper_accumulator = 0;
    }
};


static void samAnimate(float elapsedTime)
{

    sam_sprite.setTexture(sam_texture);
    sam_sprite.setTextureRect(sf::IntRect(0, 0, 1000, 1000));
    sam_accumulator += elapsedTime * animate_speed;

    if (sam_accumulator > 1 && sam_accumulator < 2)
    {
        sam_sprite.setTextureRect(sf::IntRect(1000, 0, 1000, 1000));
    } 
    else if (sam_accumulator > 2 && sam_accumulator < 3)
    {
        sam_sprite.setTextureRect(sf::IntRect(2000, 0, 1000, 1000));
    }
    else if (sam_accumulator > 3 && sam_accumulator < 4)
    {
        sam_sprite.setTextureRect(sf::IntRect(3000, 0, 1000, 1000));
    }
    else if (sam_accumulator > 4 && sam_accumulator < 5)
    {
        sam_sprite.setTextureRect(sf::IntRect(4000, 0, 1000, 1000));
    }
    else if (sam_accumulator > 5 && sam_accumulator < 6)
    {
        sam_sprite.setTextureRect(sf::IntRect(5000, 0, 1000, 1000));
    }
    else if (sam_accumulator > 6 && sam_accumulator < 7)
    {
        sam_sprite.setTextureRect(sf::IntRect(6000, 0, 1000, 1000));
    }
    else if (sam_accumulator > 7 && sam_accumulator < 8)
    {
        sam_sprite.setTextureRect(sf::IntRect(7000, 0, 1000, 1000));
    }
    else if (sam_accumulator > 8 && sam_accumulator < 9)
    {
        sam_sprite.setTextureRect(sf::IntRect(8000, 0, 1000, 1000));
    }
    else if (sam_accumulator > 9 && sam_accumulator < 10)
    {
        sam_sprite.setTextureRect(sf::IntRect(9000, 0, 1000, 1000));
    }
    else if (sam_accumulator > 10 && sam_accumulator < 11)
    {
        sam_sprite.setTextureRect(sf::IntRect(10000, 0, 1000, 1000));
    }
    else if (sam_accumulator > 11 && sam_accumulator < 12)
    {
        sam_sprite.setTextureRect(sf::IntRect(11000, 0, 1000, 1000));
    }
    else if (sam_accumulator > 12 && sam_accumulator < 13)
    {
        sam_sprite.setTextureRect(sf::IntRect(12000, 0, 1000, 1000));
    }
    else if (sam_accumulator > 13 && sam_accumulator < 14)
    {
        sam_sprite.setTextureRect(sf::IntRect(13000, 0, 1000, 1000));
    }
    else if (sam_accumulator > 14 && sam_accumulator < 15)
    {
        sam_sprite.setTextureRect(sf::IntRect(14000, 0, 1000, 1000));
        sam_accumulator = 0;
    }

};