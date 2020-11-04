#include <iostream>
#include <math.h>
#include <stdlib.h>
// #include <IVisible.hpp>
// #include <IAnimatable.hpp>
// #include <IMovable.hpp>
// #include <IPlayer.hpp>
// #include <IPlatform.hpp>
#if __EMSCRIPTEN__
	#include <emscripten/emscripten.h>
	#include <SDL2/SDL.h>
#else
	#include <SDL.h>
    #include <SDL_image.h>
#endif

//game objects
SDL_Window* window;
SDL_Surface icon;
// sf::Music music;
// sf::Music collision_sound;
// sf::Music jump_sound;
SDL_Surface background_texture;
SDL_Surface background_sprite;
SDL_Surface bike_texture;
SDL_Surface* street_texture;
SDL_Surface* screen_surface;
SDL_Event event;
// Player* sam;
// std::vector <Platform> platforms;
// TTF_Font font;
// sf::Text text("Score: ", font);

float time_of_click;
bool collided;
bool jumping; 
bool debug_render = false;
int game_time;
float game_score;


const int platform_gap = 650;  // This controls the distance between spawned platforms
const int platform_midsection_upper_bound = 3; // This is the upper bound count of how many midsections a platform may have
const int platform_height_range = 200;
const int platform_speed = -20;
const int player_jump_height = -35; 
const int player_jump_speed = 20;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
bool quit = false;

//Game consts

//const sf::Color background_color(91, 10, 145);


// static void checkCollision()
// { 
//     // for (int platformCount = 0; platformCount < platforms.size(); platformCount++)
//     // {
//     //     for (int colliderCount = 0; colliderCount < platforms[platformCount].getBounds().size(); colliderCount++)
//     //     {
//     //         if (sam->bounds.getGlobalBounds().intersects(platforms[platformCount].getBounds()[colliderCount].getGlobalBounds()))
//     //         {
//     //             collided = true;
//     //         }
//     //     }
//     // }
// };

// static int round(int n) 
// {  
//     int a = (n / 10) * 10; 
//     int b = a + 10; 
//     return (n - a > b - n)? b : a; 
// } 

// static Platform generateNextPlatform(Platform previousPlatform)
// {
//     int xoffset = (previousPlatform.getMidSectionCount() * platform_gap);
//     int nextXPosition = (previousPlatform.getX() + platform_gap);
//     int nextMidSectionCount = rand() % platform_midsection_upper_bound;
//     int yoffset = round(rand() % platform_height_range + (previousPlatform.getY() - (platform_height_range / 2)));

//     if (yoffset > 520)
//     {
//         yoffset = 520;
//     }
    
//     if (yoffset < 120)
//     {
//         yoffset = 120;
//     }

//     return Platform(street_texture, nextMidSectionCount, nextXPosition , yoffset);
// }


// static void destroyPlatforms()
// {
//     // if (platforms[0].getX() < -2000)
//     // {
//     //     platforms.erase(platforms.begin());
//     // }
// }

// static void update(float elapsed)
// {
//     // game_score += (game_time.asSeconds() + elapsed);
//     // std::string score = "Score: " + std::to_string(game_score);
//     // text.setString(score);
//     // while (platforms.size() < 7)
//     // {
//     //     platforms.push_back(generateNextPlatform(platforms[platforms.size() - 1]));
//     // }

//     // for (int i = 0; i < platforms.size(); i++)
//     // {
//     //     platforms[i].move(platform_speed, 0);
//     // }

//     // collided = false;
//     // checkCollision();
//     // float delta = elapsed * 60;

//     // if (jumping)
//     // {
//     //     time_of_click += delta;
//     //     if (time_of_click > 15)
//     //     {
//     //         jumping = false;
//     //     }
//     // }
    
//     // if (jumping)
//     // {
//     //     sam->move(0, player_jump_height);
//     // } 
//     // if (!collided)
//     // {
//     //     sam->move(0, player_jump_speed);
//     // }

//     // destroyPlatforms();
// };



// static void render()
// {
//     // window.draw(background_sprite);
//     // for (int i = 0; i < platforms.size(); i++)
//     // {
//     //     platforms[i].render(window);
//     // }
//     // window.draw(text);
//     // sam->render(window);
// };

// static void debugRender()
// {
//     // for (int i = 0; i < platforms.size(); i++)
//     // {
//     //     platforms[i].renderCollider(window);
//     // }
   
//     // sam->renderCollider(window);
// };

static void input(SDL_Event e)
{
    //User requests quit
    if( e.type == SDL_QUIT )
    {
        quit = true;
    }
    // if (event.type == sf::Event::Closed) 
    // {
        
    //     window.close();
    // }
    
    // if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
    // {
    //     window.close();
    // }

    // if (event.type == sf::Event::KeyPressed && event.key.code ==sf::Keyboard::F1)
    // {
    //     debug_render =! debug_render;
    // }

    // if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
    // {
    //     if (collided)
    //     {
    //         if (!jumping)
    //         {
    //             time_of_click = 0;
    //             jump_sound.play();
    //             collision_sound.play();
    //         }
    //         jumping = true;
    //     }
    // }

}

// static void loadResources()
// {
// 	// icon.loadFromFile("resources/sam_icon_2.png");
//     // background_texture.loadFromFile("resources/background.jpg");
//     // bike_texture.loadFromFile("resources/bike_sheet_sam.png");
//     // music.openFromFile("resources/cyber_sam.wav");
//     // jump_sound.openFromFile("resources/cartoon_jump.wav");
//     // collision_sound.openFromFile("resources/collision.wav");
//     // street_texture = new sf::Texture();
//     // street_texture->loadFromFile("resources/street_sheet.png");
//     // font.loadFromFile("resources/sansation.ttf");
// };

static void init()
{
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        throw SDL_GetError();
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "TkyoSpaghetti", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            throw SDL_GetError();
		}
		else
		{
			//Get window surface
		    screen_surface = SDL_GetWindowSurface( window );
		}
	}

	return;
    // window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    // window.setFramerateLimit(60);
    // sam = new Player(bike_texture);
    // Platform platform = Platform(street_texture, 10, -50, 480); 
    // platforms.push_back(platform);
    // sam->move(110, 450);  
    // text.setCharacterSize(30);
    // text.setStyle(sf::Text::Bold);
    // text.setFillColor(sf::Color::White);
    // text.move(1040, 0);
    // background_sprite.setTexture(background_texture);
    // music.play();
    // music.setLoop(true);
};



int main(int, char const**)
{
    // Create the main window
    // loadResources();
    init();

    // sf::Clock clock;
    // game_time = clock.restart();
    // Start the game loop
    while (quit != true)
    {
        //Event handler
        SDL_Event e;


        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            input(e);
        }

    //     //Apply the image
    //     SDL_BlitSurface( gXOut, NULL, gScreenSurface, NULL );

    //     //Update the surface
         SDL_UpdateWindowSurface( window );
    //    // sf::Time elapsed = clock.restart();
        
        // while (window.pollEvent(event))
        // {
        //     input();
        // }
        
        // window.clear(background_color);
        // sam->animate(elapsed.asSeconds());

        // update(elapsed.asSeconds());
        // render();

        // if (debug_render)
        // {
        //     debugRender();
        // }
        
        // window.display();
        
    };
    // music.~Music();
    // jump_sound.~Music();
    // collision_sound.~Music();
    return EXIT_SUCCESS;
};