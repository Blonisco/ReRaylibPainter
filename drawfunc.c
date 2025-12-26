#include "raylib.h"
#include "screens.h"
// 画一个两点确定地矩形
//@param:
// posX_a posY_a:第一点的坐标
// posX_b posY_b:对角点的坐标
// colot 颜色
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
