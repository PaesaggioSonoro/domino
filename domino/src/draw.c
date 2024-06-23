#include "draw.h"
/**
 * @file draw.c
 * @brief This file contains the functions to draw the game on the screen
 * @details This file contains all the functions and utils to draw everything is on the screen, almost every function inside this file is ran every frame to allow visual
 * feedback to the player and responsiveness to the input
 */

/**
 * @brief Draws the menu
 */
void drawMenu();
/**
 * @brief Draws the selection rectangle around the given rectangle
 * @param rect Original rectangle to draw selection on
 * @param offset Offset of the selection rectangle
 * @param size Size of the selection rectangle border
 * @param r Red channel
 * @param g Green channel
 * @param b Blue channel
 * @param a Alpha channel
 */
void drawRectSelection(SDL_Rect rect, int offset, int size, int r, int g, int b, int a);
/**
 * @brief Linear interpolation between two values
 * @param start Start value
 * @param end End value
 * @param t Interpolation amount
 * @return Interpolated value
 */
float lerp(float start, float end, float t);
/**
 * @brief Utils function to check if something is animating
 * @return True if animation running
 */
bool animationComplete();
static bool AnimatingMenu = false; /**< True if the menu is animating */
static bool AnimatingCardWrong = false; /**< True if the animation of the "wrong card placement" is running */
/**
 * @brief Draws the cards on the screen
 * @param cards Array of cards data to draw
 */
void drawCards(Card* cards);

void draw(){
    // Clear screen
    SDL_SetRenderDrawColor( game.renderer, 0x00, 0x00, 0x00, 0x00 );

    switch (game.status) {
        case GameStatus_MENU:
            drawMenu();
            break;
        case GameStatus_ANIMATING:
            if(AnimatingMenu){
                drawMenu();
            } else if (AnimatingCardWrong){
                drawCards(game.cards);
            }
            break;
        case GameStatus_PLAYING:
            drawInfo(true, game.info, true);
            drawInfo(false, game.info2, false);
            drawCards(game.cards);
            drawScore(game.score1, game.score2);
            break;
        case GameStatus_GAMEOVER:
            drawCards(game.cards);
            drawScore(game.score1, game.score2);
            if(game.mode == GameMode_SINGLE_PLAYER){
                drawInfo(true, "Game Over", true);
                drawInfo(false, "Press Enter to play again", false);
            } else {
                if(game.score1 > game.score2)
                    drawInfo(true, "You won!", true);
                else if(game.score1 < game.score2)
                    drawInfo(true, "You lose!", true);
                else
                    drawInfo(true, "Draw", true);
                drawInfo(false, "Press Enter to play again", false);
            }
            break;
    }
//    drawTessera(game.tessera1, game.tessera2, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, false);
//    drawString("cacca", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, game.fontBig, 0, 0);

}

static SDL_Texture* MenuTex_SinglePlayer;
static SDL_Rect MenuDest_SinglePlayer;
static SDL_Texture* MenuTex_WithAI;
static SDL_Rect MenuDest_WithAI;
void initMenu(){
    SDL_Surface* surface1;
    SDL_Surface* surface2;
    surface1 = IMG_Load(getAbsolutePath("/assets/single_player.png"));
    surface2 = IMG_Load(getAbsolutePath("/assets/with_ai.png"));

    // loads image to our graphics hardware memory.
    MenuTex_SinglePlayer = SDL_CreateTextureFromSurface(game.renderer, surface1);
    MenuTex_WithAI = SDL_CreateTextureFromSurface(game.renderer, surface2);

    // clears main-memory
    SDL_FreeSurface(surface1);
    SDL_FreeSurface(surface2);

    // dest let us control our image position
    // so that we can move it with our keyboard.

    // connects our texture with MenuDest_SinglePlayer to control position
    SDL_QueryTexture(MenuTex_SinglePlayer, NULL, NULL, &MenuDest_SinglePlayer.w, &MenuDest_SinglePlayer.h);
    SDL_QueryTexture(MenuTex_WithAI, NULL, NULL, &MenuDest_WithAI.w, &MenuDest_WithAI.h);
    SDL_SetTextureBlendMode(MenuTex_SinglePlayer, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(MenuTex_WithAI, SDL_BLENDMODE_BLEND);


    // adjust height and width of our image box.
    MenuDest_SinglePlayer.w *= MENU_IMAGES_SIZE;
    MenuDest_SinglePlayer.h *= MENU_IMAGES_SIZE;
    MenuDest_WithAI.w *= MENU_IMAGES_SIZE;
    MenuDest_WithAI.h *= MENU_IMAGES_SIZE;

    MenuDest_SinglePlayer.x = SCREEN_WIDTH / 3 - MenuDest_SinglePlayer.w / 2;
    MenuDest_SinglePlayer.y = SCREEN_HEIGHT / 4 - MenuDest_SinglePlayer.h / 2;

    MenuDest_WithAI.x = (SCREEN_WIDTH / 1.5) - MenuDest_WithAI.w / 2;
    MenuDest_WithAI.y = (SCREEN_HEIGHT / 1.5) - MenuDest_WithAI.h / 2;
}

static float AnimationMenuCurrentStep = 0;
static float AnimationMenuStepIncrement = 0;
static Uint8 MenuImageAlpha = 255;
static int MenuAnimationWait = 0;
/**
 * @brief Runs the menu animation
 * @param steps Number of steps of the animation
 * @param wait Duration of animation in frames
 */
void animateMenu(int steps, int wait){
    MenuAnimationWait = wait;
    AnimatingMenu = true;
    AnimationMenuStepIncrement = 1.0f/(float)steps;
    MenuImageAlpha = 255;
}
/**
 * @brief Resets the menu animation data to default values
 */
void resetMenuAnimation(){
    AnimatingMenu = false;
    AnimationMenuCurrentStep = 0;
    MenuImageAlpha = 255;
    SDL_SetTextureAlphaMod(MenuSinglePlayerSelected ? MenuTex_WithAI : MenuTex_SinglePlayer, MenuImageAlpha);
}


void drawMenu() {
    if(AnimatingMenu){

        AnimationMenuCurrentStep += AnimationMenuStepIncrement;
        if(AnimationMenuCurrentStep >= 1){
            if(MenuAnimationWait > 0){
                MenuAnimationWait--;
            } else {
                AnimationMenuCurrentStep = 0;
                AnimatingMenu = false;
                // print MenuImageAlpha
            }
        } else {
            MenuImageAlpha = lerp(255, 0, AnimationMenuCurrentStep);
            SDL_SetTextureAlphaMod(MenuSinglePlayerSelected ? MenuTex_WithAI : MenuTex_SinglePlayer, MenuImageAlpha);
        }
    }else {
        if (MenuSinglePlayerSelected) {
            drawRectSelection(MenuDest_SinglePlayer, 10, 6, RED);
        } else if (MenuWithAISelected) {
            drawRectSelection(MenuDest_WithAI, 10, 6, RED);
        }
    }
    SDL_RenderCopy(game.renderer, MenuTex_SinglePlayer, NULL, &MenuDest_SinglePlayer);
    SDL_RenderCopy(game.renderer, MenuTex_WithAI, NULL, &MenuDest_WithAI);
}

/**
 * @brief Puts the program to sleep for a given amount of time between each frame
 * @details This function is used to limit the frame rate of the game and avoid using all the CPU to create useless frames
 * @param frameLimit
 */
void delay(unsigned int frameLimit){
    unsigned int ticks = SDL_GetTicks();
    if(frameLimit < ticks){
        return;
    }
    if(frameLimit > ticks + 16){
        SDL_Delay(16);
    } else{
        SDL_Delay(frameLimit - ticks);
    }
}

int AnimationCardWrongWait = 0;
int AnimationCardWrongCurrentStep = 0;
/**
 * @brief Animates the card when it's placed in the wrong position
 * @param wait Duration of the animation in frames
 */
void animateCardWrong(int wait){
    AnimatingCardWrong = true;
    AnimationCardWrongWait = wait;
}
#pragma clang diagnostic push
#pragma ide diagnostic ignored "NullDereference"
void drawCards(Card* cards){
    int player1 = 0;
    int player2 = 0;
    int table = 0;
    Card * choosing = NULL;
    for(int i = 0; i < N_CARDS*2; i++){
        if(cards[i].position == CardPosition_TABLE) table++;
        else if(cards[i].position == CardPosition_ChoosingL || cards[i].position == CardPosition_ChoosingR) choosing = &cards[i];
        else if(cards[i].ofPlayer) player1++;
        else player2++;
    }
    // draw player 1 cards
    int y = SCREEN_HEIGHT-SCREEN_HEIGHT/5.5;
    int x = SCREEN_WIDTH/2 - (CARD_WIDTH * player1 + CARDS_SPACE_BETWEEN * (player1-1))/2;
    for(int i = 0; i < N_CARDS*2; i++){
        if(cards[i].ofPlayer && cards[i].position == CardPosition_HAND){
            drawTesseraStruct(cards[i], x, y);
            x += CARD_WIDTH + CARDS_SPACE_BETWEEN;
        }
    }

    if(game.mode == GameMode_WITH_AI){
        // draw player 2 cards
        y = SCREEN_HEIGHT/7;
        x = SCREEN_WIDTH/2 - (CARD_WIDTH * player2 + CARDS_SPACE_BETWEEN * (player2-1))/2;
        for(int i = 0; i < N_CARDS*2; i++){
            if(!cards[i].ofPlayer && cards[i].position == CardPosition_HAND){
                drawTesseraStruct(cards[i], x, y);
                x += CARD_WIDTH + CARDS_SPACE_BETWEEN;
            }
        }
    }

    // draw table cards
    int tableY = SCREEN_HEIGHT/2 - CARD_HEIGHT/2;
    int tableCurrentX = SCREEN_WIDTH/2 - (CARD_WIDTH * table + CARDS_SPACE_BETWEEN * (table - 1)) / 2;
    int tableStartX = tableCurrentX;
    Card *current = game.firstUsed;
    while(current != NULL){
        drawTesseraStruct(*current, tableCurrentX, tableY);
        tableCurrentX += CARD_WIDTH + CARDS_SPACE_BETWEEN;
        current = current->next;
    }

    // draw choosing card
    if(choosing){
        if(choosing->position == CardPosition_ChoosingL){
            drawTesseraStruct(*choosing, tableStartX - CARD_WIDTH - CARDS_SPACE_BETWEEN*2, tableY);
        } else {
            drawTesseraStruct(*choosing, tableCurrentX +CARDS_SPACE_BETWEEN*2, tableY);
        }
    }
    {

    }
    if(AnimatingCardWrong){
        AnimationCardWrongCurrentStep++;
        if(AnimationCardWrongCurrentStep > AnimationCardWrongWait){
            choosing->wrong = false;
            choosing->position = CardPosition_HAND;
            AnimatingCardWrong = false;
            AnimationCardWrongCurrentStep = 0;
        }
    }
}
#pragma clang diagnostic pop

void drawRectSelection(SDL_Rect rect, int offset, int size, int r, int g, int b, int a){
    SDL_SetRenderDrawColor(game.renderer, r, g, b, a);
    SDL_Rect top = {rect.x - offset - size, rect.y - offset - size, rect.w + offset * 2 + size, size};
    SDL_RenderFillRect(game.renderer, &top);
    SDL_Rect bottom = {rect.x - offset - size, rect.y + rect.h + offset, rect.w + offset * 2 + size*2, size};
    SDL_RenderFillRect(game.renderer, &bottom);
    SDL_Rect left = {rect.x - offset - size, rect.y - offset - size, size, rect.h + offset * 2 + size};
    SDL_RenderFillRect(game.renderer, &left);
    SDL_Rect right = {rect.x + rect.w + offset, rect.y - offset - size, size, rect.h + offset * 2 + size};
    SDL_RenderFillRect(game.renderer, &right);
    SDL_SetRenderDrawColor(game.renderer, BLACK);
}



bool animationComplete(){
    return !(AnimatingMenu || AnimatingCardWrong);
}

float lerp(float start, float end, float t) {
    return (1 - t) * start + t * end;
}