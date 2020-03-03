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
sf::Music music;
sf::Texture bike_texture;
sf::Texture* street_texture;
sf::Event event;
Player* sam;
std::vector <Platform> platforms;
sf::Font font;
sf::Text text("Score: ", font);

float time_of_click;
bool collided;
bool jumping; 
bool debug_render = false;
sf::Time game_time;
float game_score;


const int platform_gap = 650;  // This controls the distance between spawned platforms
const int platform_midsection_upper_bound = 3; // This is the upper bound count of how many midsections a platform may have
const int platform_height_range = 200;
const int platform_speed = -20;
const int player_jump_height = -35; 
const int player_jump_speed = 20;

//Game consts

const sf::Color background_color(91, 10, 145);


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

static int round(int n) 
{  
    int a = (n / 10) * 10; 
    int b = a + 10; 
    return (n - a > b - n)? b : a; 
} 

static Platform generateNextPlatform(Platform previousPlatform)
{
    int xoffset = (previousPlatform.getMidSectionCount() * platform_gap);
    int nextXPosition = (previousPlatform.getX() + platform_gap);
    int nextMidSectionCount = rand() % platform_midsection_upper_bound;
    int yoffset = round(rand() % platform_height_range + (previousPlatform.getY() - (platform_height_range / 2)));

    if (yoffset > 520)
    {
        yoffset = 520;
    }
    
    if (yoffset < 120)
    {
        yoffset = 120;
    }

    return Platform(street_texture, nextMidSectionCount, nextXPosition , yoffset);
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
    game_score += (game_time.asSeconds() + elapsed);
    std::string score = "Score: " + std::to_string(game_score);
    text.setString(score);
    while (platforms.size() < 7)
    {
        platforms.push_back(generateNextPlatform(platforms[platforms.size() - 1]));
    }

    for (int i = 0; i < platforms.size(); i++)
    {
        platforms[i].move(platform_speed, 0);
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
        sam->move(0, player_jump_height);
    } 
    if (!collided)
    {
        sam->move(0, player_jump_speed);
    }

    destroyPlatforms();
};



static void render()
{    
    for (int i = 0; i < platforms.size(); i++)
    {
        platforms[i].render(window);
    }
    window.draw(text);
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
    font.loadFromFile("resources/sansation.ttf");
 
};

static void init()
{
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setFramerateLimit(60);
    sam = new Player(bike_texture);
    Platform platform = Platform(street_texture, 10, -50, 480); 
    platforms.push_back(platform);
    sam->move(110, 450);  
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    text.move(1040, 0);
//   music.play();
//   music.setLoop(true);
};



int main(int, char const**)
{
    // Create the main window
    loadResources();
    init();

    sf::Clock clock;
    game_time = clock.restart();
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