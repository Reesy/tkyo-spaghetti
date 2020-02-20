#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <IVisible.hpp>
#include <IAnimatable.hpp>
#include <IMovable.hpp>
#include <IPlayer.hpp>
#include <IPlatform.hpp>

//game objects
sf::RenderWindow window(sf::VideoMode(1280, 720), "Tkyo Spaghetti");

sf::Image icon;

sf::Texture floor_texture;
sf::Texture bike_texture;
sf::Music music;
sf::RectangleShape bike_box(sf::Vector2f(100, 45));

sf::RectangleShape floor_box(sf::Vector2f(1280, 50));



sf::Texture street_texture;
sf::Sprite street_sprite_beginning;
sf::Sprite street_sprite_middle;
sf::Sprite street_sprite_end;
sf::Event event;

Player* sam;
Platform* platform;


float time_of_click;
bool collided;
bool jumping; 
bool game_over;
bool debug_render = false;

sf::Color background_color(91, 10, 145);


static void checkCollision()
{ 
    if (sam->bounds.getGlobalBounds().intersects(floor_box.getGlobalBounds()))
    {
        collided = true;
    }
};

static void update(float elapsed)
{
    float delta = elapsed * 60;

    if (jumping)
    {
        time_of_click += delta;
        if (time_of_click > 15)
        {
            jumping = false;
        }
    }

    if (jumping)
    {
        sam->move(0, -10);
    } 
    else if (!collided)
    {
        sam->move(0, 4);
    }
};



static void render()
{    
    platform->render(window);
    sam->render(window);
    
};

static void debugRender()
{
    platform->renderCollider(window);
    sam->renderCollider(window);
};

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

    if (event.type == sf::Event::KeyPressed && event.key.code ==sf::Keyboard::F1)
    {
        debug_render =! debug_render;
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
    {
        if (collided)
        {
            if (!jumping)
            {
                time_of_click = 0;
            }

            collided = false;
            jumping = true;
        }
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
    {
       platform->move(-10, 0);
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
    {
        platform->move(10, 0);
    }
}

static void loadResources()
{
	icon.loadFromFile("resources/sam_icon_2.png");

    bike_texture.loadFromFile("resources/bike_sheet.png");
 
	music.openFromFile("resources/cyber_sam.wav");

    street_texture.loadFromFile("resources/street_sheet.png");
};

static void init()
{
    
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setFramerateLimit(60);
    sam = new Player(bike_texture);
    platform = new Platform(street_texture, 3);
    sam->move(110, 450);
    floor_box.move(0, 600);


   // music.play();
   // music.setLoop(true);
};



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
    
        window.clear(background_color);
        sam->animate(elapsed.asSeconds());
        update(elapsed.asSeconds());
        checkCollision();
        
        render();

        if (debug_render)
        {
            debugRender();
        }
        
        window.display();
        
    };

    sam->move(10, 10);
    
    return EXIT_SUCCESS;

};