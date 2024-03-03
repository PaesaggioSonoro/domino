#include "tessera.h"

enum corners {
    TWO,
    ALL
};

static void drawCentralCircle(int x, int y){
    DrawCircleFill(game.renderer,
               x + CARD_CIRCLES_AREA/2,
               y + CARD_CIRCLES_AREA/2,
               CARD_CIRCLE_RADIUS);
}

static void drawCornerCirclees(int x, int y, enum corners corner){
    switch(corner){
        case TWO:
            DrawCircleFill(game.renderer, x + CARD_CIRCLES_AREA - CARD_CIRCLE_RADIUS, y + CARD_CIRCLE_RADIUS, CARD_CIRCLE_RADIUS);
            DrawCircleFill(game.renderer, x + CARD_CIRCLE_RADIUS, y + CARD_CIRCLES_AREA - CARD_CIRCLE_RADIUS, CARD_CIRCLE_RADIUS);
            break;
        case ALL:
            DrawCircleFill(game.renderer, x + CARD_CIRCLES_AREA - CARD_CIRCLE_RADIUS, y + CARD_CIRCLE_RADIUS, CARD_CIRCLE_RADIUS);
            DrawCircleFill(game.renderer, x + CARD_CIRCLE_RADIUS, y + CARD_CIRCLES_AREA - CARD_CIRCLE_RADIUS, CARD_CIRCLE_RADIUS);
            DrawCircleFill(game.renderer, x + CARD_CIRCLES_AREA - CARD_CIRCLE_RADIUS, y + CARD_CIRCLES_AREA - CARD_CIRCLE_RADIUS, CARD_CIRCLE_RADIUS);
            DrawCircleFill(game.renderer, x + CARD_CIRCLE_RADIUS, y + CARD_CIRCLE_RADIUS, CARD_CIRCLE_RADIUS);
            break;
    }
}

static void drawBorderCircles(int x, int y){
    DrawCircleFill(game.renderer, x + CARD_CIRCLES_AREA/2, y + CARD_CIRCLE_RADIUS, CARD_CIRCLE_RADIUS);
    DrawCircleFill(game.renderer, x + CARD_CIRCLES_AREA/2, y + CARD_CIRCLES_AREA - CARD_CIRCLE_RADIUS, CARD_CIRCLE_RADIUS);
}

static void drawNumber(int n, int x, int y){
    switch(n){
        case 1:
            drawCentralCircle(x, y);
            break;
        case 2:
            drawCornerCirclees(x, y, TWO);
            break;
        case 3:
            drawCentralCircle(x, y);
            drawCornerCirclees(x, y, TWO);
            break;
        case 4:
            drawCornerCirclees(x, y, ALL);
            break;
        case 5:
            drawCentralCircle(x, y);
            drawCornerCirclees(x, y, ALL);
            break;
        case 6:
            drawCornerCirclees(x, y, ALL);
            drawBorderCircles(x, y);
            break;
    }

}



void drawTesseraVal(int val1, int val2, int x, int y, bool selected){
    SDL_Rect fillRect = { x, y, CARD_WIDTH, CARD_HEIGHT};
    SDL_SetRenderDrawColor( game.renderer, CARD_COLOR);
    SDL_RenderFillRect( game.renderer, &fillRect);

    {
        // Render borders
        SDL_SetRenderDrawColor( game.renderer, CARD_BORDER_COLOR);

        SDL_Rect border1 = { x, y, CARD_WIDTH, CARD_BORDER};
        SDL_RenderFillRect( game.renderer, &border1);

        SDL_Rect border2 = { x, y + CARD_HEIGHT - CARD_BORDER, CARD_WIDTH, CARD_BORDER};
        SDL_RenderFillRect( game.renderer, &border2);

        SDL_Rect border3 = { x, y, CARD_BORDER, CARD_HEIGHT};
        SDL_RenderFillRect( game.renderer, &border3);

        SDL_Rect border4 = { x + CARD_WIDTH - CARD_BORDER, y, CARD_BORDER, CARD_HEIGHT};
        SDL_RenderFillRect( game.renderer, &border4);

        if(selected){
            // use CARD_SELECTED_BORDER and CARD_SELECTED_BORDER_PADDING
            // draw borders as lines above
            SDL_SetRenderDrawColor( game.renderer, CARD_BORDER_COLOR_SELECTED);
            SDL_Rect border1 = { x - CARD_SELECTED_BORDER_PADDING, y - CARD_SELECTED_BORDER_PADDING, CARD_WIDTH + 2 * CARD_SELECTED_BORDER_PADDING, CARD_SELECTED_BORDER};
            SDL_RenderFillRect( game.renderer, &border1);

            SDL_Rect border2 = { x - CARD_SELECTED_BORDER_PADDING, y + CARD_HEIGHT - CARD_SELECTED_BORDER + CARD_SELECTED_BORDER_PADDING, CARD_WIDTH + 2 * CARD_SELECTED_BORDER_PADDING, CARD_SELECTED_BORDER};
            SDL_RenderFillRect( game.renderer, &border2);

            SDL_Rect border3 = { x - CARD_SELECTED_BORDER_PADDING, y - CARD_SELECTED_BORDER_PADDING, CARD_SELECTED_BORDER, CARD_HEIGHT + 2 * CARD_SELECTED_BORDER_PADDING};
            SDL_RenderFillRect( game.renderer, &border3);

            SDL_Rect border4 = { x + CARD_WIDTH - CARD_SELECTED_BORDER + CARD_SELECTED_BORDER_PADDING, y - CARD_SELECTED_BORDER_PADDING, CARD_SELECTED_BORDER, CARD_HEIGHT + 2 * CARD_SELECTED_BORDER_PADDING};
            SDL_RenderFillRect( game.renderer, &border4);
        }
    }

    {
        // Render spacer
        SDL_SetRenderDrawColor( game.renderer, CARD_SPACER_COLOR);
        SDL_Rect spacer = { x + CARD_WIDTH/2 - CARD_SPACER_SIZE/2,
                            y + CARD_SPACER_PADDING,
                            CARD_SPACER_SIZE,
                            CARD_HEIGHT - 2 * CARD_SPACER_PADDING};
        SDL_RenderFillRect( game.renderer, &spacer);
    }
    SDL_SetRenderDrawColor( game.renderer, CIRCLE_COLOR);
    drawNumber(val1, x + CARD_INTERNAL_PADDING, y + CARD_INTERNAL_PADDING);
    drawNumber(val2, x + CARD_WIDTH/2 + CARD_INTERNAL_PADDING, y + CARD_INTERNAL_PADDING);
}

void drawTesseraStruct(Card t, int x, int y){
    drawTesseraVal(t.value1, t.value2, x, y, t.selected);
}
