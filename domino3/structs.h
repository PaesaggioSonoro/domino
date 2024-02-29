#include "defs.h"

typedef struct Game
{
    int score;
    SDL_Renderer *renderer;
    SDL_Window *win;
    TTF_Font *font;
} Game;

typedef struct Control
{
    int up, down, left, right, fire;
} Control;