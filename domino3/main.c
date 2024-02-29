#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <stdio.h>
#include "game.h"

int main(int argc, char *argv[])
{

    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    GameLoop();

    return 0;
}