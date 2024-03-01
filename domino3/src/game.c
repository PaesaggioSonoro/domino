#include "game.h"

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
//            else if(input.enter){
//                if(MenuSinglePlayerSelected){
//                    game.status = GameStatus_PLAYING;
//                } else if(MenuWithAISelected){
//                    game.status = GameStatus_PLAYING;
//                }
            break;
        case GameStatus_PLAYING:
            DistrubuteCards();
            break;
        case GameStatusGAMEOVER:
            break;
    }
}

bool inputReleased(){
    return !(input.up || input.down || input.left || input.right || input.enter);
}