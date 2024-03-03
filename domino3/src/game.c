#include "game.h"

#define CHECK_INPUTS if(someInput()) waitingNextInput = true
#define CHECK_INPUT_UP if(input.up) waitingNextInput = true
#define CHECK_INPUT_DOWN if(input.down) waitingNextInput = true
#define CHECK_INPUT_LEFT if(input.left) waitingNextInput = true
#define CHECK_INPUT_RIGHT if(input.right) waitingNextInput = true


int nextStatus = GameStatus_NULL;

// MENU
bool MenuSinglePlayerSelected = false;
bool MenuWithAISelected = false;

// GAME
bool SelectingFromTable = false;

static bool inputReleased();
static bool someInput();
static Card * getFirstUserCard();
static Card * getLastUserCard();
static Card * getSelectedUserCard();

void DistrubuteCards(){
    srand(time(NULL));
    // fill cards array with random values
    for(int i = 0; i < N_CARDS*2; i++){
        game.cards[i].value1 = rand() % 6 + 1;
        game.cards[i].value2 = rand() % 6 + 1;
        game.cards[i].selected = false;
        game.cards[i].used = false;
        game.cards[i].first = i%N_CARDS == 0;
        game.cards[i].player1 = i < N_CARDS;
        if(i%N_CARDS != 0) game.cards[i-1].next = &game.cards[i];
        // set previous field (half should not have previous)
        if(i!=0 && i!=N_CARDS) game.cards[i].previous = &game.cards[i-1];
    }
}

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
            if(input.up||input.right){
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
            } else if(input.down||input.left){
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
            }
            else if(input.enter) {
                if (MenuSinglePlayerSelected) {
                    game.status = GameStatus_ANIMATING;
                    animateMenu(20, 30);
                    nextStatus = GameStatus_PLAYING;
                    game.mode = GameMode_SINGLE_PLAYER;
                }
            }
            break;
        case GameStatus_PLAYING:
            if(!SelectingFromTable){
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
                    }
                }
            }
            break;
        case GameStatus_GAMEOVER:
            break;
    }

}

static Card * getFirstUserCard(){
    for(int i = 0; i < N_CARDS; i++){
        if(!game.cards[i].used) return &game.cards[i];
    }
    return NULL;
}
static Card * getLastUserCard(){
    for(int i = N_CARDS-1; i >= 0; i--){
        if(!game.cards[i].used) return &game.cards[i];
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
    return input.up || input.down || input.left || input.right || input.enter;
}


bool inputReleased(){
    return !(input.up || input.down || input.left || input.right || input.enter);
}