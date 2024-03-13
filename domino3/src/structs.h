#include "defs.h"

typedef struct Card
{
    int val1, val2;
    bool ofPlayer;
    bool selected;
    struct Card * next; // next card on table or hand (based on "used")
    struct Card * previous;
    bool wrong;
    enum CardPosition position;
} Card;

typedef struct Game
{
    enum GameStatus status;
    enum GameMode mode;
    SDL_Renderer *renderer;
    SDL_Window *win;
    TTF_Font *fontBig;
    TTF_Font *fontSmall;
    int score1;
    int score2;
    struct Card cards[N_CARDS*2];
    struct Card *firstUsed;
    struct Card *lastUsed;
    char *info;
    char *info2;
    char *path;
} Game;

typedef struct Control
{
    int up, down, left, right, enter, esc;
} Control;
