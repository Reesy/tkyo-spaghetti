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

sf::Texture street_texture;
sf::Sprite street_sprite_beginning;
sf::Sprite street_sprite_middle;
sf::Sprite street_sprite_end;
sf::Event event;

Player* sam;
Platform* platform;

float time_of_click;
float scene_time = 0;

bool collided;
bool jumping; 
bool game_over;
bool debug_render = false;

sf::Color background_color(91, 10, 145);


static void checkCollision()
{ 
    for (int i = 0; i < platform->getBounds().size(); i++)
    {
        if (sam->bounds.getGlobalBounds().intersects(platform->getBounds()[i].getGlobalBounds()))
        {
            collided = true;
        }
    }

};

static void update(float elapsed)
{
    scene_time =+ elapsed;

    platform->move(-10, 0);

    if (scene_time > 2)
    {
      //  platform = new Platform(street_texture, 0, -50, 480); 
        scene_time = 0;
    }

    collided = false;
    checkCollision();
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
    if (!collided)
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

    bike_texture.loadFromFile("resources/bike_sheet_sam.png");
 
	music.openFromFile("resources/cyber_sam.wav");

    street_texture.loadFromFile("resources/street_sheet.png");
};

static void init()
{
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setFramerateLimit(60);
    sam = new Player(bike_texture);
    platform = new Platform(street_texture, 0, -50, 480); 
    sam->move(110, 450);
//   music.play();
//   music.setLoop(true);
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
        render();

        if (debug_render)
        {
            debugRender();
        }
        
        window.display();
        
    };
    return EXIT_SUCCESS;
};