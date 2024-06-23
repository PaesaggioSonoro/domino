#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * @file defs.h
 * @brief This file contains the definitions of the game
 *
 */

// COLORS
/**
 * @def BLACK
 * RGB Color Black
 */
/**
 * @def RED
 * RGB Color Red
 */
#define BLACK 0x00, 0x00, 0x00, 0xFF
#define RED 0xFF, 0x00, 0x00, 0xFF

/**
 * @def SCREEN_WIDTH
 * @brief Width of the screen
 */
/**
 * @def SCREEN_HEIGHT
 * @brief Height of the screen
 */
#define SCREEN_WIDTH 1250
#define SCREEN_HEIGHT 600

/**
 * @def CARD_HEIGHT
 * @brief Height of the single card
 */
/**
 * @def CARD_WIDTH
 * @brief Width of the single card
 */
/**
 * @def CARD_BORDER
 * @brief Pixels of border of the card
 */
#define CARD_HEIGHT 40
#define CARD_WIDTH (2 * CARD_HEIGHT)
#define CARD_BORDER 3

/**
 * @def CARD_INTERNAL_PADDING
 * @brief Padding between the card and the circles
 */
/**
 * @def CARD_CIRCLE_RADIUS
 * @brief Radius of the circles inside the card
 */
#define CARD_INTERNAL_PADDING (CARD_HEIGHT/10)
#define CARD_CIRCLE_RADIUS (CARD_HEIGHT/10)

/**
 * @def CARD_SPACER_SIZE
 * @brief Size of the spacer between the circles inside the card
 */
/**
 * @def CARD_SPACER_PADDING
 * @brief Padding between the spacer and the circles inside the card
 */
/**
 * @def CARDS_SPACE_BETWEEN
 * @brief Space between a card and the next one
 */
#define CARD_SPACER_SIZE 1
#define CARD_SPACER_PADDING 6
#define CARDS_SPACE_BETWEEN 10

/**
 * @def CARD_SELECTED_BORDER
 * @brief Size of border if card selected
 */
/**
 * @def CARD_SELECTED_BORDER_PADDING
 * @brief Padding of the border if card selected
 */
#define CARD_SELECTED_BORDER 5
#define CARD_SELECTED_BORDER_PADDING 2

/**
 * @def CARD_COLOR
 * @brief Background color of the card
 */
 /**
  * @def CIRCLE_COLOR
  * @brief Color of the circles inside the card
  */
#define CARD_COLOR 0xFE, 0xED, 0xD0, 0xFF
#define CIRCLE_COLOR BLACK
#define CARD_BORDER_COLOR 0x89, 0x84, 0x5B, 0xFF
#define CARD_BORDER_COLOR_SELECTED RED

#define CARD_SPACER_COLOR BLACK

#define MENU_IMAGES_SIZE 1.0

// GAME
/**
 * @def N_CARDS
 * @brief Number of cards in the game for every player
 */
#define N_CARDS 8

/**
 * @def AI_THINK_TIME
 * @brief Delay between each AI move
 */
#define AI_THINK_TIME 20


//derived
#define CARD_CIRCLES_AREA (CARD_HEIGHT - 2 * CARD_INTERNAL_PADDING)

// FUNCTIONS


// enums

/**
 * @enum GameStatus
 * @brief Enum for the game status
 */
enum GameStatus
{
    GameStatus_NULL, /*!< enum is not initialized */
    GameStatus_MENU, /*!< game is in the menu */
    GameStatus_PLAYING, /*!< game is playing */
    GameStatus_GAMEOVER, /*!< game is over, player can restart and will go back to the menu */
    GameStatus_ANIMATING /*!< game is doing some animations and will go back to GameStatus_PLAYING when done */
};

/**
 * @enum GameMode
 * @brief Enum for the game mode
 */
enum GameMode
{
    GameMode_SINGLE_PLAYER, /*!< single player mode */
    GameMode_WITH_AI, /*!< player vs AI mode */
    GameMode_NULL /*!< enum is not initialized (i.e. menu) */
};

/**
 * @enum CardPosition
 * @brief Enum for the card position
 */
enum CardPosition {
    CardPosition_TABLE, /*!< card is on the table */
    CardPosition_HAND, /*!< card is in the player's hand */
    CardPosition_ChoosingR, /*!< card is being placed by the player on the right side of the table (but still not placed) */
    CardPosition_ChoosingL /*!< card is being chosen by the player on the left side of the table (but still not placed) */
};

