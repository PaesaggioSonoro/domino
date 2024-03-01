#include "draw.h"



void draw(){
    // Clear screen
    SDL_SetRenderDrawColor( game.renderer, 0x00, 0x00, 0x00, 0x00 );
    SDL_RenderClear( game.renderer );

    drawTessera(game.tessera1, game.tessera2, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, false);
}



void delay(unsigned int frameLimit)
{
    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks)
    {
        return;
    }

    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }

    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}