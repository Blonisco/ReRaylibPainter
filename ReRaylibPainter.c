#include "raylib.h"
#include "screens.h"

// font
Color font_color = BLACK;
int font_size    = 40;
// mode init
static Mode mode_current = MENU;

int
main ()
{
        InitWindow (1400, 1280, "RaylibPainter");

        init_menu ();
        while (!WindowShouldClose () && mode_current != EXIT)
                {
                        Mode next_mode = mode_current;

                        // update mode

                        switch (mode_current)
                                {
                                case MENU:
                                        update_mode_menu ();
                                        next_mode = return_mode_menu ();
                                        break;
                                case DRAW:
                                        update_mode_draw ();
                                        next_mode = return_mode_draw ();
                                        break;
                                case FILE:
                                        break;
                                case EXIT:
                                        break;
                                default:
                                        break;
                                }
                        // update mode

                        // *** 核心修改：状态转换 ***
                        if (next_mode != mode_current)
                                {
                                        mode_current = next_mode;
                                        // 切换状态后应调用新状态的初始化函数
                                        if (mode_current == DRAW)
                                                {
                                                        init_draw ();
                                                }
                                        else if (mode_current == MENU)
                                                {
                                                        init_menu ();
                                                }
                                }
                        // draw
                        BeginDrawing ();
                        ClearBackground (WHITE);
                        switch (mode_current)
                                {
                                case MENU:
                                        draw_menu ();
                                        break;
                                case DRAW:
                                        draw_draw ();
                                }
                        EndDrawing ();
                };
}
