#include "defs.h"


typedef struct Game
{
    int score;
    SDL_Renderer *renderer;
    SDL_Window *win;
    TTF_Font *font;
    int tessera1, tessera2;
} Game;

typedef struct Control
{
    int up, down, left, right, enter;
} Control;