#include "structs.h"


/**
 * @brief Draws a circle filled with the selected color at XY coordinates
 * @param renderer SDL Renderer
 * @param x
 * @param y
 * @param radius
 */
void DrawCircleFill(SDL_Renderer *renderer, int x, int y, int radius)
{
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}