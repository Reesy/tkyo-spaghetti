#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <IVisible.hpp>
#include <IAnimatable.hpp>
#include <IMovable.hpp>
#include <IPlayer.hpp>

//game objects
sf::RenderWindow window(sf::VideoMode(1280, 720), "Tkyo Spaghetti");

sf::Image icon;

sf::Texture floor_texture;

sf::Music music;
sf::RectangleShape bike_box(sf::Vector2f(100, 45));

sf::RectangleShape floor_box(sf::Vector2f(1280, 50));

sf::Sprite pole_dancer_sprite;
sf::Texture pole_dancer_texture;

sf::Sprite stripper_sprite;
sf::Texture stripper_texture;

sf::Texture street_texture;
sf::Sprite street_sprite_beginning;
sf::Sprite street_sprite_middle;
sf::Sprite street_sprite_end;

sf::Sprite sam_sprite;
sf::Texture sam_texture;

sf::Sprite bike_sprite;
sf::Texture bike_texture;

sf::Event event;

Player* sam;

float pole_dancer_accumulator;
float stripper_accumulator;
float sam_accumulator;
float bike_accumulator;
float animate_speed;
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
    window.draw(street_sprite_beginning);
    window.draw(street_sprite_middle);
    window.draw(street_sprite_end);
    sam->render(window);
    
};

static void debugRender()
{
    sam->renderCollider(window);
    window.draw(floor_box);
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
       //currently does nothing
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
    {
        //currently does nothing
    }
}

static void loadResources()
{
	icon.loadFromFile("resources/sam_icon_2.png");

    pole_dancer_texture.loadFromFile("resources/pole_dance_sheet.png");
    
    stripper_texture.loadFromFile("resources/stripper_twerk_sheet.png");

    sam_texture.loadFromFile("resources/sam_sprite_money_sheet.png");

    bike_texture.loadFromFile("resources/bike_sheet.png");
 
	music.openFromFile("resources/cyber_sam.wav");

    street_texture.loadFromFile("resources/street_sheet.png");
};

static void init()
{
    
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setFramerateLimit(60);
    sam = new Player(bike_texture);

    sam->move(110, 450);
 
    floor_box.move(0, 600);

    animate_speed = 7;

    street_sprite_beginning.setTexture(street_texture);
    street_sprite_middle.setTexture(street_texture);
    street_sprite_end.setTexture(street_texture);

    street_sprite_beginning.setScale(3, 3);
    street_sprite_middle.setScale(3, 3);
    street_sprite_end.setScale(3, 3);

    street_sprite_beginning.setTextureRect(sf::IntRect(0, 0, 200, 200));
    street_sprite_middle.setTextureRect(sf::IntRect(200, 0, 200, 200));
    street_sprite_end.setTextureRect(sf::IntRect(400, 0, 200, 200));


    street_sprite_beginning.move(-50, 480);
    street_sprite_middle.move(250, 480);
    street_sprite_end.move(550, 480);

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