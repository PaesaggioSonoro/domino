#include "defs.h"

/**
 * @struct Card
 * @brief Struct that holds the card data
 * @var Card::val1
 * First value of the card
 * @var Card::val2
 * Second value of the card
 * @var Card::ofPlayer
 * If the card is of the player
 * @var Card::selected
 * If the card is selected
 * @var Card::next
 * Pointer to the next card in the context (table or hand)
 * @var Card::previous
 * Pointer to the previous card in the context (table or hand)
 * @var Card::wrong
 * If the player placed the card in the wrong place (will stay true during the "wrong" animation)
 * @var Card::position
 * Position of the card (table or hand)
 */
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

/**
 * @struct Game
 * @brief Struct that holds the game data
 * @var Game::status
 * Status of the game, if playing, menu, etc
 * @var Game::mode
 * Mode of the game
 * @var Game::renderer
 * SDL renderer
 * @var Game::win
 * SDL window
 * @var Game::fontBig
 * Font for the text used in the game (big format)
 * @var Game::fontSmall
 * Font for the text used in the game (small format)
 * @var Game::score1
 * Score of player 1
 * @var Game::score2
 * Score of AI
 * @var Game::cards
 * Array of cards used in game
 * @var Game::firstUsed
 * Pointer to the first card used
 * @var Game::lastUsed
 * Pointer to the last card used
 * @var Game::info
 * Info message displayed in the game (big format)
 * @var Game::info2
 * Info message displayed in the game (small format)
 * @var Game::path
 * Path to the executable
 */
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

/**
 * @struct Control
 * @brief Struct that holds the input data
 * @var Control::up
 * If the up key is pressed
 * @var Control::down
 * If the down key is pressed
 * @var Control::left
 * If the left key is pressed
 * @var Control::right
 * If the right key is pressed
 * @var Control::enter
 * If the enter key is pressed
 * @var Control::esc
 * If the escape key is pressed
 */
typedef struct Control
{
    int up, down, left, right, enter, esc;
} Control;
