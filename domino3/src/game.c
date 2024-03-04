#include "game.h"

int nextStatus = GameStatus_NULL;

// MENU
bool MenuSinglePlayerSelected = false;
bool MenuWithAISelected = false;

// GAME
bool SelectingFromTable = false;
int inactiveTimer = 0;
#define INACTIVE_TIME 100
#define INACTIVE_MESSAGE(a, t) if(inactiveTimer > t) game.info = a;
#define INACTIVE_MESSAGE2(a, t) if(inactiveTimer > t) game.info2 = a;


bool waitingNextInput = false;

void GameLoop(){
    if(waitingNextInput && someInput()){
        return;
    } else {
        waitingNextInput = false;
    }
    if(game.status == GameStatus_ANIMATING){
        if(animationComplete()){
            game.status = nextStatus;
        }
    }
    switch (game.status) {
        case GameStatus_MENU:
            CHECK_INPUTS;
            if(input.up||input.right||input.down||input.left){
                if(MenuSinglePlayerSelected){
                    MenuSinglePlayerSelected = false;
                    MenuWithAISelected = true;
                }
                else if(MenuWithAISelected){
                    MenuSinglePlayerSelected = true;
                    MenuWithAISelected = false;
                } else {
                    MenuSinglePlayerSelected = true;
                }
            } else if(input.enter) {
                if (MenuSinglePlayerSelected) {
                    game.status = GameStatus_ANIMATING;
                    animateMenu(20, 30);
                    nextStatus = GameStatus_PLAYING;
                    game.mode = GameMode_SINGLE_PLAYER;
                } else {
                    printf("AI mode not implemented yet\n");
                }
            } else if(input.esc){
                exit(0);
            }
            break;
        case GameStatus_PLAYING:
            inactiveTimer++;
            if(someInput()){
                inactiveTimer = 0;
                game.info = "";
                game.info2 = "";
            }
            if(!SelectingFromTable){
                INACTIVE_MESSAGE("Select a card", INACTIVE_TIME);
                INACTIVE_MESSAGE2("(Press Enter)", INACTIVE_TIME*2);
                if(someInput() && !getSelectedUserCard()) {
                    CHECK_INPUTS;
                    getFirstUserCard()->selected = true;
                }
                else{
                    CHECK_INPUT_LEFT;CHECK_INPUT_RIGHT;
                    if(input.right){
                        Card * selectedCard = getSelectedUserCard();
                        selectedCard->selected = false;
                        if(selectedCard->next){
                            selectedCard->next->selected = true;
                        } else {
                            getFirstUserCard()->selected = true;
                        }
                    } else if(input.left){
                        Card * selectedCard = getSelectedUserCard();
                        selectedCard->selected = false;
                        if(selectedCard->previous){
                            selectedCard->previous->selected = true;
                        } else {
                            getLastUserCard()->selected = true;
                        }
                    } else if(input.enter){
                        CHECK_INPUT_ENTER;
                        Card * selectedCard = getSelectedUserCard();
                        if(!game.firstUsed){    // no card on table
                            if(selectedCard->next){
                                selectedCard->next->previous = selectedCard->previous;
                                selectedCard->next->selected = true;
                            }
                            if(selectedCard->previous){
                                selectedCard->previous->next = selectedCard->next;
                                if(!selectedCard->next) selectedCard->previous->selected = true;
                            }

                            selectedCard->position = CardPosition_TABLE;
                            game.firstUsed = selectedCard;
                            game.lastUsed = selectedCard;
                            selectedCard->selected = false;
                            selectedCard->next = NULL;
                            selectedCard->previous = NULL;

                            game.score1+= selectedCard->val1 + selectedCard->val2;
                            if(!checkMoves()){
                                game.status = GameStatus_GAMEOVER;
                            }
                        } else {
                            selectedCard->position = CardPosition_ChoosingL;
                            SelectingFromTable = true;
                        }
                    }
                }
            } else{
                CHECK_INPUTS;
                INACTIVE_MESSAGE("Move the card", INACTIVE_TIME);
                INACTIVE_MESSAGE2("<- -> to move, UP DOWN to swap values, ENTER to place, ESC to change card", INACTIVE_TIME*3);
                Card * selectedCard = getSelectedUserCard();
                if(selectedCard->position == CardPosition_ChoosingL && input.right){
                    selectedCard->position = CardPosition_ChoosingR;
                } else if(selectedCard->position == CardPosition_ChoosingR && input.left){
                    selectedCard->position = CardPosition_ChoosingL;
                } else if(input.up||input.down){    // rotate card
                    int temp = selectedCard->val1;
                    selectedCard->val1 = selectedCard->val2;
                    selectedCard->val2 = temp;
                } else if(input.enter){     // place card
                    if(selectedCard->position == CardPosition_ChoosingL){
                        if(selectedCard->val2 == game.firstUsed->val1){
                            placeCard(selectedCard, true);
                        } else wrongCard(selectedCard);
                    } else if(selectedCard->position == CardPosition_ChoosingR){
                        if(selectedCard->val1 == game.lastUsed->val2){
                            placeCard(selectedCard, false);
                        } else wrongCard(selectedCard);
                    }
                    SelectingFromTable = false;
                } else if(input.esc){
                    selectedCard->position = CardPosition_HAND;
                    SelectingFromTable = false;
                }
            }
            break;
        case GameStatus_GAMEOVER:
            CHECK_INPUT_ENTER;CHECK_INPUT_ESC;
            if(input.enter){
                resetMenuAnimation();
                game.status = GameStatus_MENU;
                game.score1 = 0;
                game.score2 = 0;
                DistributeCards();
            } else if(input.esc){
                exit(0);
            }
            break;
    }

}

void DistributeCards(){
    game.firstUsed = NULL;
    game.lastUsed = NULL;
    // empty cards

    srand(time(NULL));
    // fill cards array with random values
    for(int i = 0; i < N_CARDS*2; i++){
        game.cards[i].val1 = rand() % 6 + 1;
        game.cards[i].val2 = rand() % 6 + 1;
        game.cards[i].selected = false;
        game.cards[i].ofPlayer = i < N_CARDS;
        game.cards[i].position = CardPosition_HAND;
        if(i%N_CARDS != 0) game.cards[i-1].next = &game.cards[i];
        if(i!=0 && i!=N_CARDS) game.cards[i].previous = &game.cards[i-1];
    }
}

// first means at left, not first placed
static void placeCard(Card * card, bool first){
    if(card->next){
        card->next->previous = card->previous;
        card->next->selected = true;
    }
    if(card->previous){
        card->previous->next = card->next;
        if(!card->next) card->previous->selected = true;
    }
    card->selected = false;

    card->next = first? game.firstUsed : NULL;
    card->previous = first? NULL : game.lastUsed;

    if(first) {
        card->next->previous = card;
        game.firstUsed = card;
    }
    else {
        card->previous->next = card;
        game.lastUsed = card;
    }
    card->position = CardPosition_TABLE;
    if(!checkMoves()){
        game.status = GameStatus_GAMEOVER;
    }
    int points = card->val1 + card->val2;
    card->ofPlayer? (game.score1+=points) : (game.score2 += points);
}

static void wrongCard(Card * card){
    card->wrong = true;
    game.status = GameStatus_ANIMATING;
    nextStatus = GameStatus_PLAYING;
    animateCardWrong(100);
}

static int checkMoves(){
    if(game.firstUsed == NULL) return N_CARDS;
    int possibleMoves = 0;
    for(int i = 0; i < N_CARDS; i++){
        Card current = game.cards[i];
        if(current.position == CardPosition_HAND && current.ofPlayer && (
        current.val1 == game.firstUsed->val1 || current.val2 == game.firstUsed->val1 ||
        current.val1 == game.lastUsed->val2 || current.val2 == game.lastUsed->val2)) possibleMoves++;
    }
    return possibleMoves;
}
static Card * getFirstUserCard(){
    for(int i = 0; i < N_CARDS; i++){
        if(game.cards[i].position == CardPosition_HAND) return &game.cards[i];
    }
    return NULL;
}
static Card * getLastUserCard(){
    for(int i = N_CARDS-1; i >= 0; i--){
        if(game.cards[i].position == CardPosition_HAND) return &game.cards[i];
    }
    return NULL;
}
static Card * getSelectedUserCard(){
    for(int i = 0; i < N_CARDS; i++){
        if(game.cards[i].selected) return &game.cards[i];
    }
    return NULL;
}


bool someInput(){
    return input.up || input.down || input.left || input.right || input.enter || input.esc;
}
