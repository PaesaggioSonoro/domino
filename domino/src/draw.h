#include "structs.h"

/**
 * @file draw.h
 * @brief This file contains the definitions of the draw functions
 * @details See draw.c for details on draw
 */

extern Game game; /*!< Game struct that contains all the game data */
/**
 * @brief Draws text on the screen at the desired location
 * @details Relies on SDL2_ttf library to render text
 * @param text Pointer to the text to be rendered
 * @param x X coordinate of the text
 * @param y Y coordinate of the text
 * @param font Pointer to the font to be used
 * @param centerX If equal to 1, the text will be centered on the x axis
 * @param centerY If equal to 1, the text will be centered on the y axis
 */
extern void drawString(char *text, int x, int y, TTF_Font *font, int centerX, int centerY);
/**
 * @brief Draws a single card on the screen at the desired location
 * @param t Data of card to be drawn
 * @param x X coordinate of the card
 * @param y Y coordinate of the card
 */
extern void drawTesseraStruct(Card t, int x, int y);
extern bool MenuSinglePlayerSelected; /*!< True if the single player mode is selected in the menu */
extern bool MenuWithAISelected; /*!< True if the multiplayer mode is selected in the menu */
/**
 * @brief Draws the game board on the screen
 */
extern void drawScore(int score1, int score2);
/**
 * @brief Draws an info text on the screen
 * @param up
 * @param text
 * @param big
 */
extern void drawInfo(bool up, char *text, bool big);
/**
 * @brief Converts a relative path to an absolute path
 */
extern char * getAbsolutePath(char *relativePath);
