#include <iostream>
#include <stdlib.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>

//game objects
sf::RenderWindow window(sf::VideoMode(1280, 720), "Tkyo Spaghetti");


sf::Image icon;
// Load a background to display
sf::Texture background_texture;

//pipe textures
sf::Texture pipe_texture;
sf::Texture paused_icon;

sf::Sprite paused_sprite;
sf::Sprite background;
sf::Sprite floor_sprite;
sf::Music music;

sf::RectangleShape birdBox(sf::Vector2f(55, 45));

sf::RectangleShape floor_box(sf::Vector2f(1280, 50));


sf::Font font;
sf::Text text("So beta, wow", font, 50);

sf::Texture birdTexture1;
sf::Sprite bird_sprite;

sf::Texture birdTexture2;

sf::Texture birdTexture3;
sf::Event event;

int gap = 140; //change this to increase difficulty by making gaps from each pillar wider
int pipe_gap; // This is the vertical gap between the pair of piped
int currentdistance;
int frameCounter;
int score;
float currentTimeSlice;
float accumulator;
float animateSpeed;
bool started;
bool countBlock;
bool collided;
bool endState;
bool flight; // this is true when the user has input a jump command for a specific unit of time.
bool flapping;
float timeOfClick;

static void checkCollision()
{ 
    if (birdBox.getGlobalBounds().intersects(floor_box.getGlobalBounds()))
    {
        collided = true;
    }
}

static void update(float elapsed)
{
    float delta = elapsed * 60;
    int speed = 5;
     
    checkCollision();

    if (flight)
    {
        timeOfClick += delta;
        if (timeOfClick > 15)
        {
            flight = false;
        }
    }
    
    if (flight)
    {
        bird_sprite.move(0, -4);
        birdBox.move(0, -4);
    } 
    else
    {
        bird_sprite.move(0, 4);
        birdBox.move(0, 4);
    }
}


static void birdAnimate(float elapsedTime){
    bird_sprite.setTexture(birdTexture1);
    accumulator += elapsedTime * animateSpeed;
  
    if (accumulator > 1 && accumulator < 2)
    {
        bird_sprite.setTexture(birdTexture1);
    }
    else if (accumulator > 2 && accumulator < 3)
    {
        bird_sprite.setTexture(birdTexture2);
    }
    else if (accumulator > 3 && accumulator < 4)
    {
        bird_sprite.setTexture(birdTexture3);
    }
    else if (accumulator > 4)
    {
        bird_sprite.setTexture(birdTexture2);
        accumulator = 0;
    }
}

static void render()
{
    window.draw(floor_sprite);
    window.draw(bird_sprite);
}

static void input()
{
    
    // Close window: exit
    if (event.type == sf::Event::Closed) 
    {
        window.close();
    }
    
    // Escape pressed: exit
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
    {
        window.close();
    }
    
    // plays music
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
    {
        timeOfClick = 0;
        flight = true;
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::K)
    {
        collided = false;
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
    pipe_texture.loadFromFile("resources/flappy2.png", sf::IntRect(150, 0, 150, 50));
	paused_icon.loadFromFile("resources/flappy.png", sf::IntRect(242, 197, 40, 13));
	birdTexture1.loadFromFile("resources/flappy.png", sf::IntRect(220, 120, 20, 20));
	birdTexture2.loadFromFile("resources/flappy.png", sf::IntRect(261, 86, 20, 20));
	birdTexture3.loadFromFile("resources/flappy.png", sf::IntRect(261, 60, 20, 20));
	font.loadFromFile("resources/sansation.ttf");
	music.openFromFile("resources/nice_music.ogg");
}

static void init()
{

    text.setColor(sf::Color::Black);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setFramerateLimit(60);
    background.setScale(3, 3);
    background.setTexture(background_texture);
    floor_sprite.setScale(10, 3);
    floor_sprite.setTexture(pipe_texture);
    paused_sprite.setTexture(paused_icon);
    paused_sprite.move(130, 200);
    paused_sprite.setScale(4,4);
    pipe_gap = 20;
    floor_box.move(0, 600);
    bird_sprite.setTexture(birdTexture1);
    bird_sprite.setScale(4, 4);
    bird_sprite.move(160, 240);
    birdBox.move(178,258);
    floor_sprite.move(0, 600);
    music.play();
    currentdistance = 0;
    collided = false;
    started = true;
    endState = false;
    frameCounter = 0;
    
    animateSpeed = 5;
    timeOfClick = 0;
    flight = false;
    flapping = false;
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
        
        // Clear screen
        window.clear();
    
        birdAnimate(elapsed.asSeconds());
        render();
        if (collided == false && started == true)
        {
            update(elapsed.asSeconds());
        }
    
        window.display();
        
    }

    return EXIT_SUCCESS;
    
}



