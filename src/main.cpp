#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <IVisible.hpp>
#include <IAnimatable.hpp>
#include <IMovable.hpp>
#include <IPlayer.hpp>
#include <IPlatform.hpp>

#if __EMSCRIPTEN__
	#include <emscripten/emscripten.h>
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
#else
	#include <SDL.h>
	#include <SDL_image.h>
#endif

//game objects
//(sf::VideoMode(1280, 720), "Tkyo Spaghetti");
// sf::Image icon;
// sf::Music music;
// sf::Music collision_sound;
// sf::Music jump_sound;

// sf::Font font;
// sf::Text text("Score: ", font);

uint32_t  startTime = 0;
uint32_t  current_time = 0;
double elapsed_time = 0;
double accumulator = 0;
float time_of_click;
float game_score;
bool collided;
bool jumping; 
bool debug_render = false;
bool quit = false;

//Game consts
const int platform_gap = 650;  // This controls the distance between spawned platforms
const int platform_midsection_upper_bound = 3; // This is the upper bound count of how many midsections a platform may have
const int platform_height_range = 200;
const int platform_speed = -20;
const int player_jump_height = -35; 
const int player_jump_speed = 20;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Event* event = NULL;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* background_texture = NULL;
SDL_Texture* background_sprite = NULL;
SDL_Texture* bike_texture = NULL;
SDL_Texture* street_texture = NULL;
Player* sam;
SDL_Rect* source_rect = NULL;
SDL_Rect* target_rect = NULL;
//std::vector <Platform*> platforms;

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren)
{
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr)
	{
        printf("Failed to load image\n", file.c_str());
	}
	return texture;
}

void checkCollision()
{   
    // for (int platformCount = 0; platformCount < platforms.size(); platformCount++)
    // {
    //     for (int colliderCount = 0; colliderCount < platforms[platformCount].getBounds().size(); colliderCount++)
    //     {
    //         if (sam->bounds.getGlobalBounds().intersects(platforms[platformCount].getBounds()[colliderCount].getGlobalBounds()))
    //         {
    //             collided = true;
    //         }
    //     }
    // }
};

int round(int n) 
{  
    int a = (n / 10) * 10; 
    int b = a + 10; 
    return (n - a > b - n)? b : a; 
} 

Platform generateNextPlatform(Platform previousPlatform)
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


void destroyPlatforms()
{
    // if (platforms[0].getX() < -2000)
    // {
    //     platforms.erase(platforms.begin());
    // }
}

void update(float elapsed)
{
   // game_score += (game_time.asSeconds() + elapsed);
    //std::string score = "Score: " + std::to_string(game_score);
    ///text.setString(score);
    // while (platforms.size() < 7)
    // {
    //     platforms.push_back(generateNextPlatform(platforms[platforms.size() - 1]));
    // }

    // for (int i = 0; i < platforms.size(); i++)
    // {
    //     platforms[i].move(platform_speed, 0);
    // }

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



void render()
{
    
    SDL_SetRenderDrawColor(renderer, 91, 10, 145, 255);
    SDL_RenderClear(renderer);
    //sam->render(renderer);
    SDL_RenderCopy(renderer, background_texture, source_rect, target_rect);
    sam->render(renderer);
    SDL_RenderPresent(renderer);
//     window.draw(background_sprite);
//     for (int i = 0; i < platforms.size(); i++)
//     {
//         platforms[i].render(window);
//     }
//    // window.draw(text);
//     sam->render(window);
};

void debugRender()
{
    // for (int i = 0; i < platforms.size(); i++)
    // {
    //     platforms[i].renderCollider(window);
    // }
   
    // sam->renderCollider(window);
};

void input()
{
    if (event->type == SDL_QUIT)
    {
        quit = true;
    }      
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
    //             // jump_sound.play();
    //             // collision_sound.play();
    //         }
    //         jumping = true;
    //     }
    // }

}

void loadResources()
{
    background_texture = loadTexture("resources/background.jpg", renderer);
    bike_texture = loadTexture("resources/bike_sheet_sam.png", renderer);
    street_texture = loadTexture("resources/street_sheet.png", renderer);
    
    //icon.loadFromFile("resources/sam_icon_2.png");
    // music.openFromFile("resources/cyber_sam.wav");
    // jump_sound.openFromFile("resources/cartoon_jump.wav");
    // collision_sound.openFromFile("resources/collision.wav");
    //font.loadFromFile("resources/sansation.ttf");
};


void init()
{
    //window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    //window.setFramerateLimit(60);
    
    sam = new Player(bike_texture);
    Platform platform = Platform(street_texture, 10, -50, 480);
    
    //platforms.push_back(platform);
    
    sam->move(110, 450);  
    
    // text.setCharacterSize(30);
    // text.setStyle(sf::Text::Bold);
    // text.setFillColor(sf::Color::White);
    // text.move(1040, 0);
        
    // background_sprite.setTexture(background_texture);
    // music.play();
    // music.setLoop(true);

};

void gameLoop()
{   
    startTime = SDL_GetTicks();

    while (SDL_PollEvent(event))
    {
        input();
    }

    sam->animate(elapsed_time);

    // update(elapsed.asSeconds());
    render();

    // if (debug_render)
    // {
    //     debugRender();
    // }
    
    // window.display();
    current_time = SDL_GetTicks();
    elapsed_time = (current_time - startTime) / 1000.0;
   
}

int main(int, char const**)
{
    
    //Start up SDL and make sure it went ok
	if ( SDL_Init (SDL_INIT_VIDEO) != 0 )
    {	
		throw "SDL could not be initialised";
	};

    window = SDL_CreateWindow("TkyoSpaghetti", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    event = new SDL_Event;
    
    loadResources();
    init();
    
    #if __EMSCRIPTEN__
		emscripten_set_main_loop(gameLoop, -1, 1);
	#else
		while (quit != true)
		{
			gameLoop();
		}
	#endif
    
  //  SDL_DestroyTexture( image );
	SDL_DestroyRenderer(renderer );
	SDL_DestroyWindow( window );
//	image = NULL;
	renderer = NULL;
	window = NULL;
	IMG_Quit();
	SDL_Quit();




    // sf::Clock clock;
    // game_time = clock.restart();
    
    // // Start the game loop
    // while (window.isOpen())
    // {
        
    //     sf::Time elapsed = clock.restart();
        
    //     while (window.pollEvent(event))
    //     {
    //         input();
    //     }
        
   
        
    // };
    // music.~Music();
    // jump_sound.~Music();
    // collision_sound.~Music();
    return EXIT_SUCCESS;
};