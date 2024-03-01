#include "init.h"

extern void closeFont(TTF_Font *);

void init(char *title){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Could not initialize SDL: %s\n", SDL_GetError());

        exit(1);
    }
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

    /* Initialise SDL_TTF */

    if (TTF_Init() < 0)
    {
        printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());

        exit(1);
    }

    /* Open a screen */
    game.win = SDL_CreateWindow(title, // creates a window
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    if (game.win == NULL)
    {
        printf("Couldn't set screen mode to %d x %d: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());

        exit(1);
    }


    game.renderer = SDL_CreateRenderer( game.win, -1, SDL_RENDERER_ACCELERATED );
    if( game.renderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        exit(1);
    }
    else
    {
        //Initialize renderer color
        SDL_SetRenderDrawColor( game.renderer, 0xFF, 0xFF, 0xFF, 0xFF );

        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
            printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
            exit(1);
        }
    }


}

void cleanup()
{
    // free the sprites
    closeFont(game.font);
    SDL_DestroyRenderer( game.renderer );
    SDL_DestroyWindow( game.win );
    TTF_Quit();
    SDL_Quit();
}