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
sf::Sprite poleDancerSprite2;
sf::Texture poleDancer1;
sf::Texture poleDancer2;
sf::Texture poleDancer3;
sf::Texture poleDancer4;
sf::Texture poleDancer5;

sf::Event event;

float birdAccumulator;
float poleDancerAccumulator;
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
    window.draw(bird_sprite);
    window.draw(poleDancerSprite);

    // window.draw(bird_box);
    // window.draw(floor_box);
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
        update(elapsed.asSeconds());
        checkCollision();
        render();
        window.display();
        
    }

    return EXIT_SUCCESS;
    
}



