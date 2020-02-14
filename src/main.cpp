#include <iostream>
#include <stdlib.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>

//game objects
sf::RenderWindow window(sf::VideoMode(1280, 720), "Tkyo Spaghetti");

sf::Image icon;

sf::Texture background_texture;

sf::Texture floor_texture;
sf::Sprite background;

sf::Sprite floor_sprite;

sf::Music music;
sf::RectangleShape bike_box(sf::Vector2f(100, 45));

sf::RectangleShape floor_box(sf::Vector2f(1280, 50));

sf::Sprite poleDancerSprite;
sf::Texture poleDancerTexture;

sf::Sprite stripperSprite;
sf::Texture stripperTexture;

sf::Sprite samSprite;
sf::Texture samTexture;

sf::Sprite bikeSprite;
sf::Texture bikeTexture;

sf::Event event;

float poleDancerAccumulator;
float stripperAccumulator;
float samAccumulator;
float bikeAccumulator;
float animateSpeed;
bool collided;
bool jumping; 
float timeOfClick;

static void checkCollision()
{ 
    if (bike_box.getGlobalBounds().intersects(floor_box.getGlobalBounds()))
    {
        collided = true;
    }
}

static void update(float elapsed)
{
    float delta = elapsed * 60;

    if (jumping)
    {
        timeOfClick += delta;
        if (timeOfClick > 15)
        {
            jumping = false;
        }
    }

    if (jumping)
    {
        bikeSprite.move(0, -10);
        bike_box.move(0, -10);
    } 
    else if (!collided)
    {
        bikeSprite.move(0, 4);
        bike_box.move(0, 4);
    }
}

static void poleDancerAnimate(float elapsedTime)
{
    poleDancerSprite.setTexture(poleDancerTexture);
    poleDancerSprite.setTextureRect(sf::IntRect(0, 0, 1000, 1000));
    poleDancerAccumulator += elapsedTime * animateSpeed;

    if (poleDancerAccumulator > 1 && poleDancerAccumulator < 2)
    {
        poleDancerSprite.setTextureRect(sf::IntRect(0, 0, 1000, 1000));
    } 
    else if (poleDancerAccumulator > 2 && poleDancerAccumulator < 3)
    {
        poleDancerSprite.setTextureRect(sf::IntRect(1000, 0, 1000, 1000));
    }
    else if (poleDancerAccumulator > 3 && poleDancerAccumulator < 4)
    {
        poleDancerSprite.setTextureRect(sf::IntRect(2000, 0, 1000, 1000));
    }
    else if (poleDancerAccumulator > 4 && poleDancerAccumulator < 5)
    {
        poleDancerSprite.setTextureRect(sf::IntRect(3000, 0, 1000, 1000));
    }
    else if (poleDancerAccumulator > 5)
    {
        poleDancerSprite.setTextureRect(sf::IntRect(4000, 0, 1000, 1000));
        poleDancerAccumulator = 0;
    }
}

static void stripperAnimate(float elapsedTime)
{
    stripperSprite.setTexture(stripperTexture);
    stripperAccumulator += elapsedTime * animateSpeed;
    stripperSprite.setTextureRect(sf::IntRect(0, 0, 1000, 1000));

    if (stripperAccumulator > 1 && stripperAccumulator < 2)
    {
        stripperSprite.setTextureRect(sf::IntRect(1000, 0, 1000, 1000));
    } 
    else if (stripperAccumulator > 2 && stripperAccumulator < 3)
    {
        stripperSprite.setTextureRect(sf::IntRect(2000, 0, 1000, 1000));
    }
    else if (stripperAccumulator > 3 && stripperAccumulator < 4)
    {
        stripperSprite.setTextureRect(sf::IntRect(3000, 0, 1000, 1000));
    }
    else if (stripperAccumulator > 4 && stripperAccumulator < 5)
    {
        stripperSprite.setTextureRect(sf::IntRect(4000, 0, 1000, 1000));
    }
    else if (stripperAccumulator > 5)
    {
        stripperSprite.setTextureRect(sf::IntRect(0, 0, 1000, 1000));
        stripperAccumulator = 0;
    }
}


static void samAnimate(float elapsedTime)
{

    samSprite.setTexture(samTexture);
    samSprite.setTextureRect(sf::IntRect(0, 0, 1000, 1000));
    samAccumulator += elapsedTime * animateSpeed;

    if (samAccumulator > 1 && samAccumulator < 2)
    {
        samSprite.setTextureRect(sf::IntRect(1000, 0, 1000, 1000));
    } 
    else if (samAccumulator > 2 && samAccumulator < 3)
    {
        samSprite.setTextureRect(sf::IntRect(2000, 0, 1000, 1000));
    }
    else if (samAccumulator > 3 && samAccumulator < 4)
    {
        samSprite.setTextureRect(sf::IntRect(3000, 0, 1000, 1000));
    }
    else if (samAccumulator > 4 && samAccumulator < 5)
    {
        samSprite.setTextureRect(sf::IntRect(4000, 0, 1000, 1000));
    }
    else if (samAccumulator > 5 && samAccumulator < 6)
    {
        samSprite.setTextureRect(sf::IntRect(5000, 0, 1000, 1000));
    }
    else if (samAccumulator > 6 && samAccumulator < 7)
    {
        samSprite.setTextureRect(sf::IntRect(6000, 0, 1000, 1000));
    }
    else if (samAccumulator > 7 && samAccumulator < 8)
    {
        samSprite.setTextureRect(sf::IntRect(7000, 0, 1000, 1000));
    }
    else if (samAccumulator > 8 && samAccumulator < 9)
    {
        samSprite.setTextureRect(sf::IntRect(8000, 0, 1000, 1000));
    }
    else if (samAccumulator > 9 && samAccumulator < 10)
    {
        samSprite.setTextureRect(sf::IntRect(9000, 0, 1000, 1000));
    }
    else if (samAccumulator > 10 && samAccumulator < 11)
    {
        samSprite.setTextureRect(sf::IntRect(10000, 0, 1000, 1000));
    }
    else if (samAccumulator > 11 && samAccumulator < 12)
    {
        samSprite.setTextureRect(sf::IntRect(11000, 0, 1000, 1000));
    }
    else if (samAccumulator > 12 && samAccumulator < 13)
    {
        samSprite.setTextureRect(sf::IntRect(12000, 0, 1000, 1000));
    }
    else if (samAccumulator > 13 && samAccumulator < 14)
    {
        samSprite.setTextureRect(sf::IntRect(13000, 0, 1000, 1000));
    }
    else if (samAccumulator > 14 && samAccumulator < 15)
    {
        samSprite.setTextureRect(sf::IntRect(14000, 0, 1000, 1000));
        samAccumulator = 0;
    }

}

static void bikeAnimate(float elapsedTime)
{
    bikeSprite.setTexture(bikeTexture);
    bikeSprite.setTextureRect(sf::IntRect(0, 0, 200, 200));
    bikeAccumulator += elapsedTime * animateSpeed;

    if (bikeAccumulator > 1 && bikeAccumulator < 2)
    {
        bikeSprite.setTextureRect(sf::IntRect(200, 0, 200, 200));
    } 
    else if (bikeAccumulator > 2 && bikeAccumulator < 3)
    {
        bikeSprite.setTextureRect(sf::IntRect(400, 0, 200, 200));
    }
    else if (bikeAccumulator > 3 && bikeAccumulator < 4)
    {
        bikeSprite.setTextureRect(sf::IntRect(600, 0, 200, 200));
    }
    else if (bikeAccumulator > 4 && bikeAccumulator < 5)
    {
        bikeSprite.setTextureRect(sf::IntRect(800, 0, 200, 200));
    }
    else if (bikeAccumulator > 5 && bikeAccumulator < 6)
    {
        bikeSprite.setTextureRect(sf::IntRect(1000, 0, 200, 200));
    }
    else if (bikeAccumulator > 6 && bikeAccumulator < 7)
    {
        bikeSprite.setTextureRect(sf::IntRect(1200, 0, 200, 200));
    }
    else if (bikeAccumulator > 7 && bikeAccumulator < 8)
    {
        bikeSprite.setTextureRect(sf::IntRect(1400, 0, 200, 200));
    }
    else if (bikeAccumulator > 8 && bikeAccumulator < 9)
    {
        bikeSprite.setTextureRect(sf::IntRect(1600, 0, 200, 200));
    }
    else if (bikeAccumulator > 9 && bikeAccumulator < 10)
    {
        bikeSprite.setTextureRect(sf::IntRect(1800, 0, 200, 200));
    }
    else if (bikeAccumulator > 10 && bikeAccumulator < 11)
    {
        bikeSprite.setTextureRect(sf::IntRect(2000, 0, 200, 200));
    }
    else if (bikeAccumulator > 11 && bikeAccumulator < 12)
    {
        bikeSprite.setTextureRect(sf::IntRect(2200, 0, 200, 200));
    }
    else if (bikeAccumulator > 12 && bikeAccumulator < 13)
    {
        bikeSprite.setTextureRect(sf::IntRect(2400, 0, 200, 200));
    }
    else if (bikeAccumulator > 13 && bikeAccumulator < 14)
    {
        bikeSprite.setTextureRect(sf::IntRect(2600, 0, 200, 200));
    }
    else if (bikeAccumulator > 14 && bikeAccumulator < 15)
    {
        bikeSprite.setTextureRect(sf::IntRect(2800, 0, 200, 200));
    }
    else if (bikeAccumulator > 15 && bikeAccumulator < 16)
    {
        bikeSprite.setTextureRect(sf::IntRect(3000, 0, 200, 200));
    }
    else if (bikeAccumulator > 16 && bikeAccumulator < 17)
    {
        bikeSprite.setTextureRect(sf::IntRect(3200, 0, 200, 200));
    }
    else if (bikeAccumulator > 17 && bikeAccumulator < 18)
    {
        bikeSprite.setTextureRect(sf::IntRect(3400, 0, 200, 200));
    }
    else if (bikeAccumulator > 18 && bikeAccumulator < 19)
    {
        bikeSprite.setTextureRect(sf::IntRect(3600, 0, 200, 200));
    }
    else if (bikeAccumulator > 19 && bikeAccumulator < 20)
    {
        bikeSprite.setTextureRect(sf::IntRect(3800, 0, 200, 200));
    }
    else if (bikeAccumulator > 20 && bikeAccumulator < 21)
    {
        bikeSprite.setTextureRect(sf::IntRect(4000, 0, 200, 200));
    }
    else if (bikeAccumulator > 21 && bikeAccumulator < 22)
    {
        bikeSprite.setTextureRect(sf::IntRect(4200, 0, 200, 200));
    }
    else if (bikeAccumulator > 22 && bikeAccumulator < 23)
    {
        bikeSprite.setTextureRect(sf::IntRect(4600, 0, 200, 200));
        bikeAccumulator = 0;
    }

}

static void render()
{
    window.draw(floor_sprite);
    window.draw(poleDancerSprite);
    window.draw(stripperSprite);
    window.draw(samSprite);
    window.draw(bikeSprite);

}

static void input()
{
    
    if (event.type == sf::Event::Closed) 
    {
        window.close();
    }
    
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
    {
        window.close();
    }
    
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
    {
        if (collided)
        {
            if (!jumping)
            {
                timeOfClick = 0;
            }

            collided = false;
            jumping = true;
        }
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
    {
       //currently does nothing
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
    {
        //currently does nothing
    }
}

static void loadResources()
{
    // Set the Icon
	icon.loadFromFile("resources/icon.png");
    background_texture.loadFromFile("resources/flappy2.png", sf::IntRect(0, 0, 145, 250));
    floor_texture.loadFromFile("resources/flappy2.png", sf::IntRect(150, 0, 150, 50));

    //poledancer textures
    poleDancerTexture.loadFromFile("resources/PoledanceSheet.png");
    
    stripperTexture.loadFromFile("resources/StripperTwerkSheet.png");

    samTexture.loadFromFile("resources/SamSpriteMoneySheet.png");

    bikeTexture.loadFromFile("resources/BikeSheet.png");
 
	music.openFromFile("resources/cyber_sam.wav");
}

static void init()
{
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setFramerateLimit(60);
    background.setScale(3, 3);
    background.setTexture(background_texture);
    floor_sprite.setScale(10, 3);
    floor_sprite.setTexture(floor_texture);
    poleDancerSprite.setScale(0.2, 0.2);
    poleDancerSprite.move(1000, 440);
 
    samSprite.setScale(0.2, 0.2);
    samSprite.move(800, 440);

    bikeSprite.move(110, 450);
    bike_box.move(165, 530);

    stripperSprite.setScale(0.2, 0.2);    
    stripperSprite.move(900, 440);

    floor_box.move(0, 600);

    floor_sprite.move(0, 600);
    music.play();
    music.setLoop(true);
    collided = false;
    animateSpeed = 7;
    jumping = false;
}

int main(int, char const**)
{
    // Create the main window
    loadResources();
    init();
    
    sf::Clock clock;
    
    
    // Start the game loop
    while (window.isOpen())
    {
        
        sf::Time elapsed = clock.restart();
        
        while (window.pollEvent(event))
        {
            input();
        }
    
        window.clear();
        poleDancerAnimate(elapsed.asSeconds());
        stripperAnimate(elapsed.asSeconds());
        samAnimate(elapsed.asSeconds());
        bikeAnimate(elapsed.asSeconds());
        update(elapsed.asSeconds());
        checkCollision();
        render();
        window.display();
        
    }

    return EXIT_SUCCESS;
    
}



