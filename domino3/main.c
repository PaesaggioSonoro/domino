#include "main.h"
extern void init(char *);
extern void cleanup(void);
extern TTF_Font *loadFont(char *, int);
extern void delay(unsigned int);
extern void getInput(void);



int main(int argc, char *argv[])
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    int go;

    init("Domino");


    atexit(cleanup);


    go = 1;

    // load things


    game.font = loadFont("D:/UNI/IAP/domino2/domino3/assets/FreeSans.ttf", 16);

    while (1){
        getInput();


        delay(frameLimit);

        frameLimit = SDL_GetTicks() + 16;
    }

}