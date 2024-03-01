#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <stdio.h>
#include "SDL2/SDL_ttf.h"
#include <stdbool.h>

// COLORS
#define WHITE 0xFF, 0xFF, 0xFF, 0xFF
#define BLACK 0x00, 0x00, 0x00, 0xFF
#define RED 0xFF, 0x00, 0x00, 0xFF

#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 1000
#define NO_STDIO_REDIRECT

#define CARD_HEIGHT 70
#define CARD_WIDTH (2 * CARD_HEIGHT)
#define CARD_BORDER 3

#define CARD_INTERNAL_PADDING 6
#define CARD_CIRCLE_RADIUS 7

#define CARD_SPACER_SIZE 1
#define CARD_SPACER_PADDING 6

#define CARD_COLOR 0xFE, 0xED, 0xD0, 0xFF
#define CIRCLE_COLOR BLACK
#define CARD_BORDER_COLOR 0x89, 0x84, 0x5B, 0xFF
#define CARD_BORDER_COLOR_SELECTED RED

#define CARD_SPACER_COLOR BLACK

//derived
#define CARD_CIRCLES_AREA (CARD_HEIGHT - 2 * CARD_INTERNAL_PADDING)


