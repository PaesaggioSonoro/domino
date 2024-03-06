#include "main.h"



#pragma clang diagnostic push
#pragma ide diagnostic ignored "LocalValueEscapesScope"
int main(int argc, char *argv[])
{
    char executable_path[1024];
    if (getcwd(executable_path, sizeof(executable_path)) != NULL) {
    } else {
        perror("getcwd() error. Failed to retrieve the current working directory.");
        return EXIT_FAILURE;
    }

    unsigned int frameLimit = SDL_GetTicks() + 16;
    int go;

    game.path = executable_path;
//    strcpy(game.path, executable_path);
    init("Domino");

    atexit(cleanup);


    go = 1;



    game.fontBig = loadFont(getAbsolutePath("/assets/ArcadeN.ttf"), 40);
    game.fontSmall = loadFont(getAbsolutePath("/assets/ArcadeN.ttf"), 20);
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
#pragma clang diagnostic pop

char * getAbsolutePath(char *relativePath){
    char *path = malloc(strlen(game.path) + strlen(relativePath) + 1);
    strcpy(path, game.path);
    strcat(path, relativePath);
    return path;
}