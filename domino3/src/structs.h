#include "defs.h"



typedef struct
{
    int status;
    SDL_Renderer *renderer;
    SDL_Window *win;
    TTF_Font *font;
    int score1;
    int score2;
} Game;

typedef struct
{
    int value1, value2;
    bool player1;
    bool selected;
    bool used;
    struct Card *next;
    struct Card *prev;
} Card;

typedef struct Control
{
    int up, down, left, right, enter;
} Control;