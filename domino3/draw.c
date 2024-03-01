#include "draw.h"

void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void draw(){
    //Clear screen
    SDL_SetRenderDrawColor( game.renderer, 0x00, 0x00, 0x00, 0x00 );
    SDL_RenderClear( game.renderer );

    //Render red filled quad
    SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    SDL_SetRenderDrawColor( game.renderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( game.renderer, &fillRect );
    drawString("ciao", 100, 10, game.font, 1, 0);


    //Render green outlined quad
    SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
    SDL_SetRenderDrawColor( game.renderer, 0x00, 0xFF, 0x00, 0xFF );
    SDL_RenderDrawRect( game.renderer, &outlineRect );

    //Draw blue horizontal line
    SDL_SetRenderDrawColor( game.renderer, 0x00, 0x00, 0xFF, 0xFF );
    SDL_RenderDrawLine( game.renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );

    DrawCircle(game.renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100);

    //Draw vertical line of yellow dots
    SDL_SetRenderDrawColor( game.renderer, 0xFF, 0xFF, 0x00, 0xFF );
    for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
    {
        SDL_RenderDrawPoint( game.renderer, SCREEN_WIDTH / 2, i );
    }
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