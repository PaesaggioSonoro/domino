#include "main.h"



int main(int argc, char *argv[])
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    int go;

    init("Domino");

    printf("porcaccioputtana\n");

    atexit(cleanup);


    go = 1;

    // load things


    game.font = loadFont("D:/UNI/IAP/domino2/domino3/assets/FreeSans.ttf", 16);


    while (1){
        getInput();

        draw();

        //Update screen
        SDL_RenderPresent( game.renderer );

        delay(frameLimit);

        frameLimit = SDL_GetTicks() + 16;
    }

}

