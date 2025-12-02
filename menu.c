#include "screens.h"

static Mode next_mode = MENU;

void
init_menu ()
{
        next_mode = MENU;
}

void
update_mode_menu ()
{
        if (IsKeyReleased (KEY_A))
                {
                        next_mode = DRAW;
                }
        else if (IsKeyReleased (KEY_S))
                {
                        next_mode = FILE;
                }
        else if (IsKeyReleased (KEY_D))
                {
                        next_mode = EXIT;
                }
}

void
draw_menu ()
{
        DrawText ("What would you like to do?\nA  Create a new "
                  "file.\nS  Open a "
                  "file\nD Exit",
                  200, 200, font_size, font_color);
}

Mode
return_mode_menu ()
{
        return next_mode;
}
