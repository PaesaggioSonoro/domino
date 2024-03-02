#include "game.h"

int nextStatus = GameStatus_NULL;

// MENU
bool MenuSinglePlayerSelected = false;
bool MenuWithAISelected = false;

bool inputReleased();
void DistrubuteCards(){

}

bool waitingNextInput = false;
void GameLoop(){
    if(waitingNextInput && !inputReleased()){
        return;
    } else {
        waitingNextInput = false;
    }
    if(nextStatus == GameStatus_ANIMATING){
        if(animationComplete()){
            game.status = nextStatus;
        }
    }
    switch (game.status) {
        case GameStatus_MENU:
            if(input.up||input.right){
                waitingNextInput = true;
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
                waitingNextInput = true;
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
                }
            }
            break;
        case GameStatus_PLAYING:
            DistrubuteCards();
            break;
        case GameStatus_GAMEOVER:
            break;
    }
}

bool inputReleased(){
    return !(input.up || input.down || input.left || input.right || input.enter);
}