#include "structs.h"

extern Game game;
extern void drawString(char *text, int x, int y, TTF_Font *font, int centerX, int centerY);
extern void drawTesseraStruct(Card t, int x, int y);
extern bool MenuSinglePlayerSelected;
extern bool MenuWithAISelected;
extern void drawScore(int score1, int score2);
extern void drawInfo(bool up, char *text, bool big);
