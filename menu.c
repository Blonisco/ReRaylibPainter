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
                        is_creating_new = 1;
                        next_mode       = FILE_READ;
                }
        else if (IsKeyReleased (KEY_S))
                {
                        is_creating_new = 0;
                        next_mode       = FILE_READ;
                }
        else if (IsKeyReleased (KEY_D))
                {
                        next_mode = EXIT;
                }
}

void
draw_menu (int file_read)
{
        DrawText ("What would you like to do?\nA  Create a new "
                  "file.\nS  Open a "
                  "file\nD Exit",
                  200, 200, font_size, font_color);
        if (file_read)
                {

                        DrawText ("Can't read file!", 30, 1250, 20, font_color);
                }
}

Mode
return_mode_menu ()
{
        return next_mode;
}
