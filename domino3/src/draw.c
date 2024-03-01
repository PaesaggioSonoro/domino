#include "draw.h"



void drawMenu();
void drawRectSelection(SDL_Rect rect, int offset, int size, int r, int g, int b, int a);


void draw(){
    SDL_RenderClear( game.renderer );
    // Clear screen
    SDL_SetRenderDrawColor( game.renderer, 0x00, 0x00, 0x00, 0x00 );

    switch (game.status) {
        case GameStatus_MENU:
            drawMenu();
            break;
    }
//    drawTessera(game.tessera1, game.tessera2, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, false);
//    drawString("cacca", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, game.font, 0, 0);

}

static SDL_Texture* MenuTex_SinglePlayer;
static SDL_Rect MenuDest_SinglePlayer;
static SDL_Texture* MenuTex_WithAI;
static SDL_Rect MenuDest_WithAI;
void initMenu(){
    SDL_Surface* surface1;
    SDL_Surface* surface2;
    surface1 = IMG_Load(PROJECT_ASSETS_PATH"/single_player.png");
    surface2 = IMG_Load(PROJECT_ASSETS_PATH"/with_ai.png");

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

    // adjust height and width of our image box.
    MenuDest_SinglePlayer.w *= 1.5;
    MenuDest_SinglePlayer.h *= 1.5;
    MenuDest_WithAI.w *= 1.5;
    MenuDest_WithAI.h *= 1.5;

    MenuDest_SinglePlayer.x = SCREEN_WIDTH / 3 - MenuDest_SinglePlayer.w / 2;
    MenuDest_SinglePlayer.y = SCREEN_HEIGHT / 4 - MenuDest_SinglePlayer.h / 2;

    MenuDest_WithAI.x = (SCREEN_WIDTH / 1.5) - MenuDest_WithAI.w / 2;
    MenuDest_WithAI.y = (SCREEN_HEIGHT / 1.5) - MenuDest_WithAI.h / 2;
}

void drawMenu() {
    if (MenuSinglePlayerSelected) {
        drawRectSelection(MenuDest_SinglePlayer, 10, 6, RED);
    } else if (MenuWithAISelected) {
        drawRectSelection(MenuDest_WithAI, 10, 6, RED);
    }
    SDL_RenderCopy(game.renderer, MenuTex_SinglePlayer, NULL, &MenuDest_SinglePlayer);
    SDL_RenderCopy(game.renderer, MenuTex_WithAI, NULL, &MenuDest_WithAI);
}


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