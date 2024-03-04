#include "main.h"



int main(int argc, char *argv[])
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    int go;

    init("Domino");

    atexit(cleanup);


    go = 1;



    game.fontBig = loadFont("D:/UNI/IAP/domino2/domino3/assets/ArcadeN.ttf", 35);
    game.fontSmall = loadFont("D:/UNI/IAP/domino2/domino3/assets/ArcadeN.ttf", 20);
    game.status = GameStatus_MENU;
    game.mode = GameMode_NULL;

    DistributeCards();

    while (1){
        getInput();
        GameLoop();
        draw();


        SDL_RenderPresent( game.renderer );
        SDL_RenderClear( game.renderer );
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;
    }

}

