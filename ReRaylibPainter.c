#include "raylib.h"
#include "screens.h"
#include <stdio.h>
#include <string.h>

// font
Color font_color    = BLACK;
int font_size       = 40;
int is_creating_new = 0;
// mode init
static Mode mode_current = MENU;

int
main (int argc, char **argv)
{
        SetTargetFPS (60);
        InitWindow (1400, 1280, "RaylibPainter");

        char file_name[1024] = "";
        FILE *fp             = NULL;
        int file_read        = 0;
        init_menu ();
        if (argc == 2)
                {
                        strncpy (file_name, argv[1], 1023);
                        mode_current = FILE_READ;
                }
        else
                {
                        mode_current = MENU;
                }

        while (!WindowShouldClose () && mode_current != EXIT)

                {
                        Mode next_mode = mode_current;

                        // update mode

                        switch (mode_current)
                                {
                                case MENU:
                                        update_mode_menu ();
                                        next_mode = return_mode_menu ();
                                        if (next_mode == FILE_READ)
                                                {
                                                        file_name[0] = '\0';
                                                }
                                        break;
                                case DRAW:
                                        update_mode_draw ();
                                        next_mode = return_mode_draw ();
                                        break;
                                case FILE_READ:

                                        fp = update_mode_file (file_name, is_creating_new);
                                        if (fp == NULL)
                                                {
                                                        file_read = 1;
                                                }
                                        else
                                                {
                                                        file_read = 0;
                                                }
                                        next_mode = return_mode_file ();
                                        break;
                                case EXIT:
                                        break;
                                default:
                                        break;
                                }
                        // update mode

                        if (next_mode != mode_current)
                                {
                                        mode_current = next_mode;
                                        if (mode_current == DRAW)
                                                {
                                                        init_draw (fp);
                                                }
                                        else if (mode_current == MENU)
                                                {
                                                        init_menu ();
                                                }
                                        else if (mode_current == FILE_READ)
                                                {
                                                        init_file ();
                                                }
                                }
                        // draw
                        BeginDrawing ();
                        ClearBackground (WHITE);
                        switch (mode_current)
                                {
                                case MENU:
                                        draw_menu (file_read);
                                        break;
                                case DRAW:
                                        draw_draw ();
                                default:
                                        break;
                                }
                        EndDrawing ();
                };
        if (fp != NULL)
                fclose (fp);
}
