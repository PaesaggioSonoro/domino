#include "init.h"

extern void closeFont(TTF_Font *);

void init(char *title){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Could not initialize SDL: %s\n", SDL_GetError());

        exit(1);
    }

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

    // triggers the program that controls
    // your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    // creates a renderer to render our images
    game.renderer = SDL_CreateRenderer(game.win, -1, render_flags);

    if (game.win == NULL)
    {
        printf("Couldn't set screen mode to %d x %d: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());

        exit(1);
    }

}

void cleanup()
{
    // free the sprites
    closeFont(game.font);
    TTF_Quit();
    SDL_Quit();
}