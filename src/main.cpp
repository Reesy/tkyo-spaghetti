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

sf::RectangleShape bird_box(sf::Vector2f(55, 45));

sf::RectangleShape floor_box(sf::Vector2f(1280, 50));

sf::Texture birdTexture1;
sf::Sprite bird_sprite;

sf::Texture birdTexture2;

sf::Texture birdTexture3;

sf::Sprite poleDancerSprite;
sf::Texture poleDancer1;
sf::Texture poleDancer2;
sf::Texture poleDancer3;
sf::Texture poleDancer4;
sf::Texture poleDancer5;

sf::Sprite stripperSprite;
sf::Texture stripper1;
sf::Texture stripper2;
sf::Texture stripper3;
sf::Texture stripper4;
sf::Texture stripper5;

sf::Sprite samSprite;
sf::Texture samTexture1;
sf::Texture samTexture2;
sf::Texture samTexture3;
sf::Texture samTexture4;
sf::Texture samTexture5;
sf::Texture samTexture6;
sf::Texture samTexture7;
sf::Texture samTexture8;
sf::Texture samTexture9;
sf::Texture samTexture10;
sf::Texture samTexture11;
sf::Texture samTexture12;
sf::Texture samTexture13;
sf::Texture samTexture14;
sf::Texture samTexture15;

sf::Sprite bikeSprite;
sf::Texture bikeTexture1;
sf::Texture bikeTexture2;
sf::Texture bikeTexture3;
sf::Texture bikeTexture4;
sf::Texture bikeTexture5;
sf::Texture bikeTexture6;
sf::Texture bikeTexture7;
sf::Texture bikeTexture8;
sf::Texture bikeTexture9;
sf::Texture bikeTexture10;
sf::Texture bikeTexture11;
sf::Texture bikeTexture12;
sf::Texture bikeTexture13;
sf::Texture bikeTexture14;
sf::Texture bikeTexture15;
sf::Texture bikeTexture16;
sf::Texture bikeTexture17;
sf::Texture bikeTexture18;
sf::Texture bikeTexture19;
sf::Texture bikeTexture20;
sf::Texture bikeTexture21;
sf::Texture bikeTexture22;
sf::Texture bikeTexture23;
sf::Texture bikeTexture24;

sf::Event event;

float birdAccumulator;
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
    if (bird_box.getGlobalBounds().intersects(floor_box.getGlobalBounds()))
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
        bird_sprite.move(0, -10);
        bird_box.move(0, -10);
    } 
    else if (!collided)
    {
        bird_sprite.move(0, 4);
        bird_box.move(0, 4);
    }
}

static void poleDancerAnimate(float elapsedTime)
{
    poleDancerSprite.setTexture(poleDancer1);
    poleDancerAccumulator += elapsedTime * animateSpeed;

    if (poleDancerAccumulator > 1 && poleDancerAccumulator < 2)
    {
        poleDancerSprite.setTexture(poleDancer1);
    } 
    else if (poleDancerAccumulator > 2 && poleDancerAccumulator < 3)
    {
        poleDancerSprite.setTexture(poleDancer2);
    }
    else if (poleDancerAccumulator > 3 && poleDancerAccumulator < 4)
    {
        poleDancerSprite.setTexture(poleDancer3);
    }
    else if (poleDancerAccumulator > 4 && poleDancerAccumulator < 5)
    {
        poleDancerSprite.setTexture(poleDancer4);
    }
    else if (poleDancerAccumulator > 5)
    {
        poleDancerSprite.setTexture(poleDancer5);
        poleDancerAccumulator = 0;
    }
}

static void stripperAnimate(float elapsedTime)
{
    stripperSprite.setTexture(stripper1);
    stripperAccumulator += elapsedTime * animateSpeed;

    if (stripperAccumulator > 1 && stripperAccumulator < 2)
    {
        stripperSprite.setTexture(stripper1);
    } 
    else if (stripperAccumulator > 2 && stripperAccumulator < 3)
    {
        stripperSprite.setTexture(stripper2);
    }
    else if (stripperAccumulator > 3 && stripperAccumulator < 4)
    {
        stripperSprite.setTexture(stripper3);
    }
    else if (stripperAccumulator > 4 && stripperAccumulator < 5)
    {
        stripperSprite.setTexture(stripper4);
    }
    else if (stripperAccumulator > 5)
    {
        stripperSprite.setTexture(stripper5);
        stripperAccumulator = 0;
    }
}


static void samAnimate(float elapsedTime)
{
    samSprite.setTexture(samTexture1);
    samAccumulator += elapsedTime * animateSpeed;

    if (samAccumulator > 1 && samAccumulator < 2)
    {
        samSprite.setTexture(samTexture2);
    } 
    else if (samAccumulator > 2 && samAccumulator < 3)
    {
        samSprite.setTexture(samTexture3);
    }
    else if (samAccumulator > 3 && samAccumulator < 4)
    {
        samSprite.setTexture(samTexture4);
    }
    else if (samAccumulator > 4 && samAccumulator < 5)
    {
        samSprite.setTexture(samTexture5);
    }
    else if (samAccumulator > 5 && samAccumulator < 6)
    {
        samSprite.setTexture(samTexture6);
    }
    else if (samAccumulator > 6 && samAccumulator < 7)
    {
        samSprite.setTexture(samTexture7);
    }
    else if (samAccumulator > 7 && samAccumulator < 8)
    {
        samSprite.setTexture(samTexture8);
    }
    else if (samAccumulator > 8 && samAccumulator < 9)
    {
        samSprite.setTexture(samTexture9);
    }
    else if (samAccumulator > 9 && samAccumulator < 10)
    {
        samSprite.setTexture(samTexture10);
    }
    else if (samAccumulator > 10 && samAccumulator < 11)
    {
        samSprite.setTexture(samTexture11);
    }
    else if (samAccumulator > 11 && samAccumulator < 12)
    {
        samSprite.setTexture(samTexture12);
    }
    else if (samAccumulator > 12 && samAccumulator < 13)
    {
        samSprite.setTexture(samTexture13);
    }
    else if (samAccumulator > 13 && samAccumulator < 14)
    {
        samSprite.setTexture(samTexture14);
    }
    else if (samAccumulator > 14 && samAccumulator < 15)
    {
        samSprite.setTexture(samTexture15);
    }
    else if (samAccumulator > 15)
    {
        samSprite.setTexture(samTexture1);
        samAccumulator = 0;
    }
}

static void bikeAnimateAnimate(float elapsedTime)
{
    bikeSprite.setTexture(bikeTexture1);
    bikeAccumulator += elapsedTime * animateSpeed;

    if (bikeAccumulator > 1 && bikeAccumulator < 2)
    {
        bikeSprite.setTexture(bikeTexture2);
    } 
    else if (bikeAccumulator > 2 && bikeAccumulator < 3)
    {
        bikeSprite.setTexture(bikeTexture3);
    }
    else if (bikeAccumulator > 3 && bikeAccumulator < 4)
    {
        bikeSprite.setTexture(bikeTexture4);
    }
    else if (bikeAccumulator > 4 && bikeAccumulator < 5)
    {
        bikeSprite.setTexture(bikeTexture5);
    }
    else if (bikeAccumulator > 5 && bikeAccumulator < 6)
    {
        bikeSprite.setTexture(bikeTexture6);
    }
    else if (bikeAccumulator > 6 && bikeAccumulator < 7)
    {
        bikeSprite.setTexture(bikeTexture7);
    }
    else if (bikeAccumulator > 7 && bikeAccumulator < 8)
    {
        bikeSprite.setTexture(bikeTexture8);
    }
    else if (bikeAccumulator > 8 && bikeAccumulator < 9)
    {
        bikeSprite.setTexture(bikeTexture9);
    }
    else if (bikeAccumulator > 9 && bikeAccumulator < 10)
    {
        bikeSprite.setTexture(bikeTexture10);
    }
    else if (bikeAccumulator > 10 && bikeAccumulator < 11)
    {
        bikeSprite.setTexture(bikeTexture11);
    }
    else if (bikeAccumulator > 11 && bikeAccumulator < 12)
    {
        bikeSprite.setTexture(bikeTexture12);
    }
    else if (bikeAccumulator > 12 && bikeAccumulator < 13)
    {
        bikeSprite.setTexture(bikeTexture13);
    }
    else if (bikeAccumulator > 13 && bikeAccumulator < 14)
    {
        bikeSprite.setTexture(bikeTexture14);
    }
    else if (bikeAccumulator > 14 && bikeAccumulator < 15)
    {
        bikeSprite.setTexture(bikeTexture15);
    }
    else if (bikeAccumulator > 15 && bikeAccumulator < 16)
    {
        bikeSprite.setTexture(bikeTexture16);
    }
    else if (bikeAccumulator > 16 && bikeAccumulator < 17)
    {
        bikeSprite.setTexture(bikeTexture17);
    }
    else if (bikeAccumulator > 17 && bikeAccumulator < 18)
    {
        bikeSprite.setTexture(bikeTexture18);
    }
    else if (bikeAccumulator > 18 && bikeAccumulator < 19)
    {
        bikeSprite.setTexture(bikeTexture19);
    }
    else if (bikeAccumulator > 19 && bikeAccumulator < 20)
    {
        bikeSprite.setTexture(bikeTexture20);
    }
    else if (bikeAccumulator > 20 && bikeAccumulator < 21)
    {
        bikeSprite.setTexture(bikeTexture21);
    }
    else if (bikeAccumulator > 21 && bikeAccumulator < 22)
    {
        bikeSprite.setTexture(bikeTexture22);
    }
    else if (bikeAccumulator > 22 && bikeAccumulator < 23)
    {
        bikeSprite.setTexture(bikeTexture23);
    }
    else if (bikeAccumulator > 23 && bikeAccumulator < 24)
    {
        bikeSprite.setTexture(bikeTexture24);
    }
    else if (bikeAccumulator > 24)
    {
        bikeSprite.setTexture(bikeTexture1);
        bikeAccumulator = 0;
    }
}

static void birdAnimate(float elapsedTime)
{
    bird_sprite.setTexture(birdTexture1);
    birdAccumulator += elapsedTime * animateSpeed;
  
    if (birdAccumulator > 1 && birdAccumulator < 2)
    {
        bird_sprite.setTexture(birdTexture1);
    }
    else if (birdAccumulator > 2 && birdAccumulator < 3)
    {
        bird_sprite.setTexture(birdTexture2);
    }
    else if (birdAccumulator > 3 && birdAccumulator < 4)
    {
        bird_sprite.setTexture(birdTexture3);
    }
    else if (birdAccumulator > 4)
    {
        bird_sprite.setTexture(birdTexture2);
        birdAccumulator = 0;
    }
}

static void render()
{
    window.draw(floor_sprite);
    //window.draw(bird_sprite);
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
        bird_sprite.setTexture(birdTexture1);
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
    {
        bird_sprite.setTexture(birdTexture2);
    }
}

static void loadResources()
{
    // Set the Icon
	icon.loadFromFile("resources/icon.png");
    background_texture.loadFromFile("resources/flappy2.png", sf::IntRect(0, 0, 145, 250));
    floor_texture.loadFromFile("resources/flappy2.png", sf::IntRect(150, 0, 150, 50));
	birdTexture1.loadFromFile("resources/flappy.png", sf::IntRect(220, 120, 20, 20));
	birdTexture2.loadFromFile("resources/flappy.png", sf::IntRect(261, 86, 20, 20));
	birdTexture3.loadFromFile("resources/flappy.png", sf::IntRect(261, 60, 20, 20));

    //poledancer textures
    poleDancer1.loadFromFile("resources/PoledanceSheet.png", sf::IntRect(0, 0, 1000, 1000));
    poleDancer2.loadFromFile("resources/PoledanceSheet.png", sf::IntRect(1000, 0, 1000, 1000));
    poleDancer3.loadFromFile("resources/PoledanceSheet.png", sf::IntRect(2000, 0, 1000, 1000));
    poleDancer4.loadFromFile("resources/PoledanceSheet.png", sf::IntRect(3000, 0, 1000, 1000));
    poleDancer5.loadFromFile("resources/PoledanceSheet.png", sf::IntRect(4000, 0, 1000, 1000));

    stripper1.loadFromFile("resources/StripperTwerkSheet.png", sf::IntRect(0, 0, 1000, 1000));
    stripper2.loadFromFile("resources/StripperTwerkSheet.png", sf::IntRect(1000, 0, 1000, 1000));
    stripper3.loadFromFile("resources/StripperTwerkSheet.png", sf::IntRect(2000, 0, 1000, 1000));
    stripper4.loadFromFile("resources/StripperTwerkSheet.png", sf::IntRect(3000, 0, 1000, 1000));
    stripper5.loadFromFile("resources/StripperTwerkSheet.png", sf::IntRect(4000, 0, 1000, 1000));

    samTexture1.loadFromFile("resources/SamSpriteMoneySheet.png", sf::IntRect(0, 0, 1000, 1000));
    samTexture2.loadFromFile("resources/SamSpriteMoneySheet.png", sf::IntRect(1000, 0, 1000, 1000));
    samTexture3.loadFromFile("resources/SamSpriteMoneySheet.png", sf::IntRect(2000, 0, 1000, 1000));
    samTexture4.loadFromFile("resources/SamSpriteMoneySheet.png", sf::IntRect(3000, 0, 1000, 1000));
    samTexture5.loadFromFile("resources/SamSpriteMoneySheet.png", sf::IntRect(4000, 0, 1000, 1000));
    samTexture6.loadFromFile("resources/SamSpriteMoneySheet.png", sf::IntRect(5000, 0, 1000, 1000));
    samTexture7.loadFromFile("resources/SamSpriteMoneySheet.png", sf::IntRect(6000, 0, 1000, 1000));
    samTexture8.loadFromFile("resources/SamSpriteMoneySheet.png", sf::IntRect(7000, 0, 1000, 1000));
    samTexture9.loadFromFile("resources/SamSpriteMoneySheet.png", sf::IntRect(8000, 0, 1000, 1000));
    samTexture10.loadFromFile("resources/SamSpriteMoneySheet.png", sf::IntRect(9000, 0, 1000, 1000));
    samTexture11.loadFromFile("resources/SamSpriteMoneySheet.png", sf::IntRect(10000, 0, 1000, 1000));
    samTexture12.loadFromFile("resources/SamSpriteMoneySheet.png", sf::IntRect(11000, 0, 1000, 1000));
    samTexture13.loadFromFile("resources/SamSpriteMoneySheet.png", sf::IntRect(12000, 0, 1000, 1000));
    samTexture14.loadFromFile("resources/SamSpriteMoneySheet.png", sf::IntRect(13000, 0, 1000, 1000));
    samTexture15.loadFromFile("resources/SamSpriteMoneySheet.png", sf::IntRect(14000, 0, 1000, 1000));

    bikeTexture1.loadFromFile("resources/BikeSheet.png", sf::IntRect(0, 0, 2000, 2000));
    bikeTexture2.loadFromFile("resources/BikeSheet.png", sf::IntRect(2000, 0, 2000, 2000));
    bikeTexture3.loadFromFile("resources/BikeSheet.png", sf::IntRect(4000, 0, 2000, 2000));
    bikeTexture4.loadFromFile("resources/BikeSheet.png", sf::IntRect(6000, 0, 2000, 2000));
    bikeTexture5.loadFromFile("resources/BikeSheet.png", sf::IntRect(8000, 0, 2000, 2000));
    bikeTexture6.loadFromFile("resources/BikeSheet.png", sf::IntRect(10000, 0, 2000, 2000));
    bikeTexture7.loadFromFile("resources/BikeSheet.png", sf::IntRect(12000, 0, 2000, 2000));
    bikeTexture8.loadFromFile("resources/BikeSheet.png", sf::IntRect(14000, 0, 2000, 2000));
    bikeTexture9.loadFromFile("resources/BikeSheet.png", sf::IntRect(16000, 0, 2000, 2000));
    bikeTexture10.loadFromFile("resources/BikeSheet.png", sf::IntRect(18000, 0, 2000, 2000));
    bikeTexture11.loadFromFile("resources/BikeSheet.png", sf::IntRect(20000, 0, 2000, 2000));
    bikeTexture12.loadFromFile("resources/BikeSheet.png", sf::IntRect(22000, 0, 2000, 2000));
    bikeTexture13.loadFromFile("resources/BikeSheet.png", sf::IntRect(24000, 0, 2000, 2000));
    bikeTexture14.loadFromFile("resources/BikeSheet.png", sf::IntRect(26000, 0, 2000, 2000));
    bikeTexture15.loadFromFile("resources/BikeSheet.png", sf::IntRect(28000, 0, 2000, 2000));
    bikeTexture16.loadFromFile("resources/BikeSheet.png", sf::IntRect(30000, 0, 2000, 2000));
    bikeTexture17.loadFromFile("resources/BikeSheet.png", sf::IntRect(32000, 0, 2000, 2000));
    bikeTexture18.loadFromFile("resources/BikeSheet.png", sf::IntRect(34000, 0, 2000, 2000));
    bikeTexture19.loadFromFile("resources/BikeSheet.png", sf::IntRect(36000, 0, 2000, 2000));
    bikeTexture20.loadFromFile("resources/BikeSheet.png", sf::IntRect(38000, 0, 2000, 2000));
    bikeTexture21.loadFromFile("resources/BikeSheet.png", sf::IntRect(40000, 0, 2000, 2000));
    bikeTexture22.loadFromFile("resources/BikeSheet.png", sf::IntRect(42000, 0, 2000, 2000));
    bikeTexture23.loadFromFile("resources/BikeSheet.png", sf::IntRect(44000, 0, 2000, 2000));
    bikeTexture24.loadFromFile("resources/BikeSheet.png", sf::IntRect(46000, 0, 2000, 2000));

	music.openFromFile("resources/nice_music.ogg");
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

    bikeSprite.setScale(0.14, 0.14);
    bikeSprite.move(110, 450);

    stripperSprite.setScale(0.2, 0.2);    
    stripperSprite.move(900, 440);

    floor_box.move(0, 600);
    bird_sprite.setTexture(birdTexture1);
    bird_sprite.setScale(4, 4);

    bird_sprite.move(160, 240);
    bird_box.move(178,258);

    floor_sprite.move(0, 600);
    music.play();
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
        birdAnimate(elapsed.asSeconds());
        poleDancerAnimate(elapsed.asSeconds());
        stripperAnimate(elapsed.asSeconds());
        samAnimate(elapsed.asSeconds());
        bikeAnimateAnimate(elapsed.asSeconds());
        update(elapsed.asSeconds());
        checkCollision();
        render();
        window.display();
        
    }

    return EXIT_SUCCESS;
    
}



