#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <IVisible.hpp>
#include <IAnimatable.hpp>
#include <IMovable.hpp>
#include <IPlayer.hpp>
#include <IPlatform.hpp>
#include <IText.hpp>
#include <IScore.hpp>

#if __EMSCRIPTEN__
	#include <emscripten/emscripten.h>
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include <SDL2/SDL_mixer.h>
#else
	#include <SDL.h>
	#include <SDL_image.h>
    #include <SDL_ttf.h>
    #include <SDL_mixer.h>
#endif

//game objects
SDL_Surface *icon = NULL;
Mix_Music *music = NULL;
Mix_Chunk *collision_sound = NULL;
Mix_Chunk *jump_sound = NULL;

float time_of_click;
float game_score;
bool collided;
bool jumping; 
bool debug_render = false;
bool quit = false;
bool paused = true;
bool hoveringOverPlayButton = false;
bool hoveringOverAudioOnButton = false;
bool hoveringOverAudioOffButton = false;
bool musicPlaying = true;

//Game consts
const int platform_gap = 650;  // This controls the distance between spawned platforms
const int platform_midsection_upper_bound = 10; // This is the upper bound count of how many midsections a platform may have
const int platform_height_range = 200;
const int platform_speed = -20;
const int player_jump_height = -35; 
const int player_jump_speed = 20;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
int music_volume = 10;
int mouseX, mouseY;

double dt = 10;
double currentTime = SDL_GetTicks();
double accumulator = 0.0;

SDL_Event* event = NULL;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* background_texture = NULL;
SDL_Texture* background_sprite = NULL;
SDL_Texture* bike_texture = NULL;
SDL_Texture* street_texture = NULL;
SDL_Texture* menu_texture = NULL;
SDL_Texture* numbers_texture = NULL;
SDL_Rect menu_src_position = {0, 0, 400, 205};
SDL_Rect menu_dst_position = {330, 200, 640, 360};
SDL_Rect play_enabled_src_position = {800, 0, 400, 205};
SDL_Rect play_disabled_src_position = {400, 0, 400, 205};
SDL_Rect audio_enabled_src_position = {1200, 0, 400, 205};
SDL_Rect audio_disabled_src_position = {1600, 0, 400, 205};
SDL_Rect play_button_location = {500, 258, 240, 100 };
SDL_Rect audio_on_button_location = {590, 415, 125, 72};
SDL_Rect audio_off_button_location = {735, 415, 131, 72};
SDL_Rect cursor_position = {0, 0, 10, 10};
SDL_Rect numbers_position = {0, 0, 100, 100};
Player* sam;
SDL_Rect* source_rect = NULL;
SDL_Rect* target_rect = NULL;
std::vector <Platform> platforms;
std::string fontLocation;
SDL_Color textColor;
TTF_Font* font;
Text* scoreText;
Score* score;


void init();

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren)
{
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr)
	{
        printf("Failed to load image\n", file.c_str());
        std::cout << "Failure reason: " << IMG_GetError() << std::endl;
	}
	return texture;
}

bool isColliding( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

void checkCollision()
{   
    for (int platformCount = 0; platformCount < platforms.size(); platformCount++)
    {
        for (int colliderCount = 0; colliderCount < platforms[platformCount].getBounds().size(); colliderCount++)
        {   
            if ( isColliding(sam->collidingRect, 
                            platforms[platformCount].getBounds()[colliderCount].collidingRect))
            {
                collided = true;
            }
        }
    }
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
    if (platforms[0].getX() < -2000)
    {
        platforms.erase(platforms.begin());
    }
}

void update(float elapsed)
{   
    game_score += elapsed;

    if (sam->getY() > SCREEN_HEIGHT)
    {
        paused = true;
        game_score = 0.0;
        init();
    }

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

    if (jumping)
    {
        time_of_click += elapsed; //jumping for 200 ms
        if (time_of_click > 200)
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

 

  //  scoreText->updateText(newScore);
    score->update(game_score / 100);
    destroyPlatforms();
};

void debugRender()
{   
    for (int i = 0; i < platforms.size(); i++)
    {
        platforms[i].renderCollider(renderer);
    }
   
    sam->renderCollider(renderer);
};

void render()
{
    SDL_SetRenderDrawColor(renderer, 91, 10, 145, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background_texture, source_rect, target_rect); 

    for (int i = 0; i < platforms.size(); i++)
    {
        platforms[i].render(renderer);
    }
    
    sam->render(renderer);
    scoreText->render(renderer);
    score->render(renderer);
    if (debug_render)
    {
        debugRender();
    }
    SDL_RenderPresent(renderer);
};

void renderMenu()
{
    SDL_SetRenderDrawColor(renderer, 91, 10, 145, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background_texture, source_rect, target_rect); 

    for (int i = 0; i < platforms.size(); i++)
    {
        platforms[i].render(renderer);
    }
    
    sam->render(renderer);
    scoreText->render(renderer);
     score->render(renderer);
    if (debug_render)
    {
        debugRender();
    }

    SDL_RenderCopy(renderer, menu_texture, &menu_src_position, &menu_dst_position);
    
    if (hoveringOverPlayButton)
    {
        SDL_RenderCopy(renderer, menu_texture, &play_enabled_src_position, &menu_dst_position);
    }
    else
    {
        SDL_RenderCopy(renderer, menu_texture, &play_disabled_src_position, &menu_dst_position);
    }

    if (musicPlaying)
    {
        SDL_RenderCopy(renderer, menu_texture, &audio_enabled_src_position, &menu_dst_position);
    }
    else
    {
        SDL_RenderCopy(renderer, menu_texture, &audio_disabled_src_position, &menu_dst_position);
    }
    SDL_RenderPresent(renderer);


}

void input()
{
    
    if (event->type == SDL_QUIT)
    {
        quit = true;
    }   
       
    mouseX = event->button.x;
    mouseY = event->button.y;

    //A slight gordion knot (really should seperate concerns but I'm bored of this project)
    if (event->type == SDL_FINGERDOWN)
    {
        mouseX = event->tfinger.x;
        mouseY = event->tfinger.y;
    }
    //this should be refactored into a seperate update function, or a menu class?
    if (isColliding(cursor_position, play_button_location))
    {
        hoveringOverPlayButton = true;
    }
    else
    {
        hoveringOverPlayButton = false;
    }

    if (isColliding(cursor_position, audio_on_button_location))
    {
        hoveringOverAudioOnButton = true;
    }
    else
    {
        hoveringOverAudioOnButton = false;
    }

    if (isColliding(cursor_position, audio_off_button_location))
    {
        hoveringOverAudioOffButton = true;
    }
    else
    {
        hoveringOverAudioOffButton = false;
    }

     
    if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_FINGERDOWN)
    {

        if (hoveringOverPlayButton)
        {
            paused = false;
        }

        if (hoveringOverAudioOnButton && paused)
        {
            musicPlaying = true;
            Mix_Volume(-1, 10);
            Mix_VolumeMusic(music_volume);
        }

        if (hoveringOverAudioOffButton && paused)
        {
            musicPlaying = false;
            Mix_Volume(-1, 0);
            Mix_VolumeMusic(0);
        }

        if (collided)
        {
            if (!jumping)
            {
                time_of_click = 0;
                Mix_PlayChannel( -1, jump_sound, 0 );
            }
            jumping = true;
        }
    
    
    }

    if (event->type == SDL_KEYDOWN)
    {
        switch (event->key.keysym.sym)
		{   
            case SDLK_F1:
                debug_render =! debug_render;
                break;
			case SDLK_SPACE:
                if (collided)
                {
                    if (!jumping)
                    {
                        time_of_click = 0;
                        Mix_PlayChannel( -1, jump_sound, 0 );
                    }
                    jumping = true;
                }
                break;
            case SDLK_p:
                paused =! paused;
                break;
			default:
				break;
		}
    }

}

void loadResources()
{

    background_texture = loadTexture("resources/background.jpg", renderer);
    bike_texture = loadTexture("resources/bikesheet.png", renderer);
    street_texture = loadTexture("resources/street_sheet.png", renderer);
    menu_texture = loadTexture("resources/menu_sheet.png", renderer);
    numbers_texture = loadTexture("resources/numbers_sheet.png", renderer);
    std::string fontpath = "/resources/sample.ttf";
    font = TTF_OpenFont(fontpath.c_str(), 40);
    if (font == nullptr)
    {
        std::cout << "Font is null in load resources: " << TTF_GetError() << std::endl;
    }

    music = Mix_LoadMUS("resources/cyber_sam.wav");
    if( music == NULL )
	{
		std::cout << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}

    jump_sound = Mix_LoadWAV("resources/cartoon_jump.wav");
    if( jump_sound == NULL )
	{
		std::cout << "Failed to load jump sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}

    collision_sound = Mix_LoadWAV("resources/collision.wav");
    if( collision_sound == NULL )
	{
		std::cout << "Failed to load collision_sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}

    icon = IMG_Load("resources/sam_icon_2.png");
    if (icon == NULL)
    {
        std::cout << "Failed to load icon! SDL_Image error: " << IMG_GetError() << std::endl;
    }
    SDL_SetWindowIcon(window, icon);
    
};

void init()
{
    sam = new Player(bike_texture);
    Platform platform = Platform(street_texture, 10, -50, 480); 

    textColor = { 255, 255, 255, 255 };
    SDL_Rect textposrect = {900, 40, 100, 50};
    scoreText = new Text(font, std::string ("Score: "), textColor, textposrect, renderer);

    platforms.clear(); // Empty any junk in the platforms vector
    platforms.push_back(platform);
    
    score = new Score(numbers_texture, 960, 45, 40, 40);
    sam->move(110, 450);  
    
    if (musicPlaying)
    {
        Mix_Volume(-1, 10);
        Mix_VolumeMusic(music_volume);
        Mix_PlayMusic( music, -1);
    }

    game_score = 0;
};

void gameLoop()
{   
    double newTime = SDL_GetTicks();
    double frameTime = newTime - currentTime;

    if (frameTime > 250)
    {
        std::cout << "Update bounded, took longer than a quater of a second" << std::endl;
        frameTime = 250;
    };

    currentTime = newTime;

    accumulator += frameTime;

    while (accumulator >= dt && !paused)
    {
        update(dt);
        sam->animate(dt);
        accumulator -= dt;
    };

    if (!paused) 
    {   
        render();
    }
    else
    {
        renderMenu();
    };

    while (SDL_PollEvent(event))
    {
        input();
        cursor_position.x = mouseX;
        cursor_position.y = mouseY;
    };
 
};

int main(int, char const**)
{
    //Start up SDL and make sure it went ok
	if ( SDL_Init (SDL_INIT_VIDEO) != 0 )
    {	
		throw "SDL could not be initialised";
	};
    
    int imgFlags = IMG_INIT_PNG;
    
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    };

 	//Also need to init SDL_ttf
	if (TTF_Init() != 0)
    {
		SDL_Quit();
		return 1;
	};

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    };
    
    window = SDL_CreateWindow("TkyoSpaghetti", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if (!SDL_RenderSetLogicalSize(renderer, 1280, 720))
    {
        std::cout << SDL_GetError() << std::endl;
    };

    event = new SDL_Event;
    
    loadResources();
    init();
    
    #if __EMSCRIPTEN__
		emscripten_set_main_loop(gameLoop, -1, 1);
	#else
		while (quit != true)
		{
			gameLoop();
		};
	#endif
    
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	renderer = NULL;
	window = NULL;
	IMG_Quit();
    TTF_Quit();
	SDL_Quit();

    return EXIT_SUCCESS;
};