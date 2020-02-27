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

sf::Texture bike_texture;
sf::Music music;
sf::RectangleShape bike_box(sf::Vector2f(100, 45));

sf::Texture* street_texture;
sf::Event event;

Player* sam;
std::vector <Platform> platforms;

float time_of_click;
float scene_time = 0;

bool collided;
bool jumping; 
bool game_over;
bool debug_render = false;

sf::Color background_color(91, 10, 145);


static void checkCollision()
{ 
    for (int platformCount = 0; platformCount < platforms.size(); platformCount++)
    {
        for (int colliderCount = 0; colliderCount < platforms[platformCount].getBounds().size(); colliderCount++)
        {
            if (sam->bounds.getGlobalBounds().intersects(platforms[platformCount].getBounds()[colliderCount].getGlobalBounds()))
            {
                collided = true;
            }
        }
    }
};

// take the x position of the last element and add 600 + 200 for every mid section
static Platform generateNextPlatform(Platform previousPlatform)
{
    int xoffset = (previousPlatform.getMidSectionCount() * 500);
    int nextXPosition = (previousPlatform.getX() + 500);
    int nextMidSectionCount = rand() % 4;
    return Platform(street_texture, nextMidSectionCount, nextXPosition , 480);
}

static void destroyPlatforms()
{
    if (platforms[0].getX() < -2000)
    {
        platforms.erase(platforms.begin());
    }
}

static void update(float elapsed)
{

    scene_time += elapsed;

    //create platforms
    while (platforms.size() < 7)
    {
        platforms.push_back(generateNextPlatform(platforms[platforms.size() - 1]));
    }

    for (int i = 0; i < platforms.size(); i++)
    {
        platforms[i].move(-10, 0);
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

    destroyPlatforms();
};



static void render()
{    
    for (int i = 0; i < platforms.size(); i++)
    {
        platforms[i].render(window);
    }
    
    sam->render(window);
};

static void debugRender()
{
    for (int i = 0; i < platforms.size(); i++)
    {
        platforms[i].renderCollider(window);
    }
   
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

}

static void loadResources()
{
	icon.loadFromFile("resources/sam_icon_2.png");

    bike_texture.loadFromFile("resources/bike_sheet_sam.png");
 
	music.openFromFile("resources/cyber_sam.wav");
    street_texture = new sf::Texture();
    street_texture->loadFromFile("resources/street_sheet.png");
};

static void init()
{
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setFramerateLimit(60);
    sam = new Player(bike_texture);
    Platform platform = Platform(street_texture, 0, -50, 480); 
    platforms.push_back(platform);
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