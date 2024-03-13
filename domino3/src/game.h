#include "structs.h"

#define CHECK_INPUTS if(someInput()) waitingNextInput = true
#define CHECK_INPUT_UP if(input.up) waitingNextInput = true
#define CHECK_INPUT_DOWN if(input.down) waitingNextInput = true
#define CHECK_INPUT_LEFT if(input.left) waitingNextInput = true
#define CHECK_INPUT_RIGHT if(input.right) waitingNextInput = true
#define CHECK_INPUT_ENTER if(input.enter) waitingNextInput = true
#define CHECK_INPUT_ESC if(input.esc) waitingNextInput = true

extern Game game;
extern Control input;
extern bool animationComplete();
extern void animateMenu(int steps, int wait);
extern void resetMenuAnimation();
extern void animateCardWrong(int wait);
extern void drawCards(Card* cards);


// STATIC
static bool someInput();
static Card * getFirstUserCard();
static Card * getLastUserCard();
static Card * getSelectedUserCard();
static int checkMoves();
static void placeCard(Card * card, bool first);
static void wrongCard(Card * card);
void DistributeCards();
static Card * bestMove();