#include "defs.h"

typedef struct Card
{
    int value1, value2;
    bool player1;
    bool selected;
    bool used;
    struct Card * next; // next card on table or hand (based on "used")
    struct Card * previous;
    bool first;
} Card;

typedef struct
{
    int status;
    enum GameMode mode;
    SDL_Renderer *renderer;
    SDL_Window *win;
    TTF_Font *font;
    int score1;
    int score2;
    struct Card cards[N_CARDS*2];
} Game;


struct Control;
typedef struct Control
{
    int up, down, left, right, enter;
} Control;
