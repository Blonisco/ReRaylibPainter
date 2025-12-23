#include "raylib.h"
#include "screens.h"

void
DrawRectanglePoints (int posX_a, int posY_a, int posX_b, int posY_b, Color color)
{
        int posX, posY, width, height;
        if (posX_a < posX_b)
                {
                        width = posX_b - posX_a;
                        posX  = posX_a;
                }
        else
                {
                        width = posX_a - posX_b;
                        posX  = posX_b;
                }
        if (posY_a < posY_b)
                {
                        height = posY_b - posY_a;
                        posY   = posY_a;
                }
        else
                {
                        height = posY_a - posY_b;
                        posY   = posY_b;
                }
        DrawRectangle (posX, posY, width, height, color);
}
