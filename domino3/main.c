#include <SDL.h>
#include <stdbool.h>
#include <stdio.h>

int main(int argc, char* args[]) {
    // Inizializza SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL non può essere inizializzato! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Crea una finestra
    SDL_Window* window = SDL_CreateWindow("Gioco del Dominio", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("La finestra non può essere creata! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Loop principale
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        // Gestione degli eventi
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Logica di gioco e rendering qui

        // Aggiorna la finestra
        SDL_GL_SwapWindow(window);
    }

    // Libera risorse e chiudi SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

//#include <stdio.h>
//#include <SDL.h>
//
//int main(int argc, char* argv[]) {
//    SDL_Init(SDL_INIT_EVERYTHING);
//    SDL_Quit();
//    return 0;
//}



