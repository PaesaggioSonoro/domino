#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>


// COLORS
#define WHITE 0xFF, 0xFF, 0xFF, 0xFF
#define BLACK 0x00, 0x00, 0x00, 0xFF
#define RED 0xFF, 0x00, 0x00, 0xFF

#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 1000
#define NO_STDIO_REDIRECT

#define CARD_HEIGHT 60
#define CARD_WIDTH (2 * CARD_HEIGHT)
#define CARD_BORDER 3

#define CARD_INTERNAL_PADDING (CARD_HEIGHT/10)
#define CARD_CIRCLE_RADIUS (CARD_HEIGHT/10)

#define CARD_SPACER_SIZE 1
#define CARD_SPACER_PADDING 6
#define CARDS_SPACE_BETWEEN 10


#define CARD_SELECTED_BORDER 5
#define CARD_SELECTED_BORDER_PADDING 2

#define CARD_COLOR 0xFE, 0xED, 0xD0, 0xFF
#define CIRCLE_COLOR BLACK
#define CARD_BORDER_COLOR 0x89, 0x84, 0x5B, 0xFF
#define CARD_BORDER_COLOR_SELECTED RED

#define CARD_SPACER_COLOR BLACK

// GAME
#define N_CARDS 7

//derived
#define CARD_CIRCLES_AREA (CARD_HEIGHT - 2 * CARD_INTERNAL_PADDING)

// FUNCTIONS


// enums

enum GameStatus
{
    GameStatus_NULL,
    GameStatus_MENU,
    GameStatus_PLAYING,
    GameStatus_GAMEOVER,
    GameStatus_ANIMATING
};

enum GameMode
{
    GameMode_SINGLE_PLAYER,
    GameMode_WITH_AI,
    GameMode_NULL
};

enum CardPosition {
    CardPosition_TABLE,
    CardPosition_HAND,
    CardPosition_ChoosingR,
    CardPosition_ChoosingL
};

