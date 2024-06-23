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
/**
 * @brief Checks if there is some input from the user
 * @details Used to avoid infinite ticks and too fast animation between possible moves. Usually used to wait for the user to release the
 * already pressed key before continuing to the next action
 * @return True if there is some input
 */
static bool someInput();
static Card * getFirstUserCard();
static Card * getLastUserCard();
static Card * getSelectedUserCard();
static int checkMoves(bool ofPlayer);
static void placeCard(Card * card, bool first);
static void wrongCard(Card * card);
/**
 * @brief Shuffles and distributes the cards to the players
 * @details Creates the array of randomized card values divided by the number of players
 */
void DistributeCards();
static Card * bestMove();