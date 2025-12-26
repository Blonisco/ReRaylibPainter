#include "raylib.h"
#include "screens.h"
#include <stdio.h>

static Mode next_mode = DRAW;
int draw_mode         = -1;
int draw_board_index  = 0;
struct draw draw_board[10000];
Color draw_color = BLACK;
int draw_size    = 50;
// line
Vector2 draw_start_mouse;
// poly
Vector2 draw_poly_points[10];
int poly_points_number = 0;
// Text
char draw_text = 'T';
static FILE *file_pointer;

void load_file (FILE *fp);
void save_file (FILE *fp);

void
init_draw (FILE *fp)
{
        next_mode          = DRAW;
        poly_points_number = 0;
        file_pointer       = fp;
        load_file (file_pointer);
}

Mode
return_mode_draw ()
{
        return next_mode;
}

void
update_mode_draw ()
{
        if (draw_mode == -1) // In "normal" mode
                {
                        if (IsKeyDown (KEY_C))
                                {
                                        draw_mode = 1; // mode1:circle
                                }
                        if (IsKeyDown (KEY_L))
                                {
                                        draw_mode = 2; // mode 2:line
                                }
                        if (IsKeyDown (KEY_P))
                                {
                                        draw_mode = 3; // mode3:Poly
                                }
                        if (IsKeyDown (KEY_T)) // mode4:Text
                                {
                                        draw_mode = 4;
                                }
                        if (IsKeyDown (KEY_R)) // Rectangle;
                                {
                                        draw_mode = 5;
                                }

                        if (IsKeyDown (KEY_W)) // save file;
                                {
                                        save_file (file_pointer);
                                }
                        if (IsKeyDown (KEY_Q))
                                {
                                        next_mode = EXIT;
                                }
                        if (IsKeyDown (KEY_M))
                                {
                                        next_mode = MENU;
                                }
                }
        else
                {
                        if (IsKeyDown (KEY_TAB))
                                {
                                        draw_mode = -1;
                                }
                }
        if (IsKeyPressed (KEY_U)) // 撤回
                {
                        if (draw_board_index > 0)
                                {
                                        draw_board_index--;
                                }
                }
        if ((int)GetMouseWheelMove () != 0)
                {
                        draw_size += (int)GetMouseWheelMove () * 3; // 滚轮选择大小
                        if (draw_size > 100)
                                draw_size = 100;
                        if (draw_size < 1)
                                draw_size = 1;
                }

        // 鼠标绘图
        if (draw_mode == 1)
                {
                        if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT))
                                {
                                        draw_board[draw_board_index].draw_board_type = 'c';
                                        draw_board[draw_board_index].position[0]
                                            = GetMousePosition ();
                                        draw_board[draw_board_index].parameter[0]     = draw_size;
                                        draw_board[draw_board_index].draw_board_color = draw_color;
                                        draw_board_index++;
                                }
                }
        else if (draw_mode == 2)
                {
                        if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT))
                                {
                                        draw_start_mouse = GetMousePosition ();
                                }

                        if (IsMouseButtonReleased (MOUSE_BUTTON_LEFT))
                                {
                                        if (draw_board_index < 10000)
                                                {
                                                        draw_board[draw_board_index].draw_board_type
                                                            = 'l';
                                                        draw_board[draw_board_index].position[0]
                                                            = draw_start_mouse;
                                                        draw_board[draw_board_index].position[1]
                                                            = GetMousePosition ();
                                                        draw_board[draw_board_index]
                                                            .draw_board_color
                                                            = draw_color;
                                                        draw_board_index++;
                                                }
                                }
                }
        else if (draw_mode == 3)
                {
                        if (IsMouseButtonReleased (MOUSE_BUTTON_LEFT))
                                {
                                        if (poly_points_number < 9)
                                                {
                                                        draw_poly_points[poly_points_number]
                                                            = GetMousePosition ();
                                                        poly_points_number++;
                                                }
                                }

                        if (IsKeyReleased (KEY_ENTER))
                                {
                                        if (poly_points_number > 1)
                                                {
                                                        for (int i = 0; i < poly_points_number; i++)
                                                                {
                                                                        draw_board[draw_board_index]
                                                                            .position[i]
                                                                            = draw_poly_points[i];
                                                                }
                                                        draw_board[draw_board_index]
                                                            .draw_board_color
                                                            = draw_color;
                                                        draw_board[draw_board_index].draw_board_type
                                                            = 'p';
                                                        draw_board[draw_board_index].parameter[0]
                                                            = poly_points_number;
                                                        draw_board_index++;
                                                        poly_points_number = 0;
                                                }
                                }
                }
        else if (draw_mode == 4)
                {
                        if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT))
                                {
                                        draw_board[draw_board_index].draw_board_color = draw_color;
                                        draw_board[draw_board_index].position[0]
                                            = GetMousePosition ();
                                        draw_board[draw_board_index].parameter[0]    = draw_text;
                                        draw_board[draw_board_index].parameter[1]    = draw_size;
                                        draw_board[draw_board_index].draw_board_type = 't';
                                        draw_board_index++;
                                }

                        int draw_text_temp = GetKeyPressed ();
                        if (draw_text_temp >= 'A' && draw_text_temp <= 'Z')
                                {
                                        draw_text = draw_text_temp;
                                }
                }
        else if (draw_mode == 5)
                {
                        if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT))
                                {
                                        draw_start_mouse = GetMousePosition ();
                                }

                        if (IsMouseButtonReleased (MOUSE_BUTTON_LEFT))
                                {
                                        if (draw_board_index < 10000)
                                                {
                                                        draw_board[draw_board_index].draw_board_type
                                                            = 'r';
                                                        draw_board[draw_board_index].position[0]
                                                            = draw_start_mouse;
                                                        draw_board[draw_board_index].position[1]
                                                            = GetMousePosition ();
                                                        draw_board[draw_board_index]
                                                            .draw_board_color
                                                            = draw_color;
                                                        draw_board_index++;
                                                }
                                }
                }
        // choose Color
        if (IsKeyPressed (KEY_ONE))
                {
                        draw_color = BLACK;
                }
        else if (IsKeyPressed (KEY_TWO))
                {
                        draw_color = BLUE;
                }
        else if (IsKeyPressed (KEY_THREE))
                {
                        draw_color = RED;
                }
        else if (IsKeyPressed (KEY_FOUR))
                {
                        draw_color = YELLOW;
                }
        else if (IsKeyPressed (KEY_FIVE))
                {
                        draw_color = GREEN;
                }
        else if (IsKeyPressed (KEY_SIX))
                {
                        draw_color = PURPLE;
                }
        else if (IsKeyPressed (KEY_SEVEN))
                {
                        draw_color = WHITE;
                }
}

void
draw_draw ()
{
        // load from data
        for (int i = 0; i <= draw_board_index - 1; i++)
                {
                        switch (draw_board[i].draw_board_type)
                                {
                                        // line
                                case 'l':
                                        DrawLine (draw_board[i].position[0].x,
                                                  draw_board[i].position[0].y,
                                                  draw_board[i].position[1].x,
                                                  draw_board[i].position[1].y,
                                                  draw_board[i].draw_board_color);
                                        break;
                                        // circle
                                case 'c':
                                        DrawCircle (draw_board[i].position[0].x,
                                                    draw_board[i].position[0].y,
                                                    draw_board[i].parameter[0],
                                                    draw_board[i].draw_board_color);
                                        break;
                                case 'p':
                                        DrawTriangleFan (draw_board[i].position,
                                                         draw_board[i].parameter[0],
                                                         draw_board[i].draw_board_color);
                                        break;
                                case 't':
                                        DrawText (TextFormat ("%c", draw_board[i].parameter[0]),
                                                  draw_board[i].position[0].x,
                                                  draw_board[i].position[0].y,
                                                  draw_board[i].parameter[1],
                                                  draw_board[i].draw_board_color);

                                        break;
                                case 'r':
                                        DrawRectanglePoints (draw_board[i].position[0].x,
                                                             draw_board[i].position[0].y,
                                                             draw_board[i].position[1].x,
                                                             draw_board[i].position[1].y,
                                                             draw_board[i].draw_board_color);
                                        break;
                                }
                }

        // draw mouse
        switch (draw_mode)
                {
                case -1:
                        DrawText ("Normal", 30, 1250, 20, font_color);
                        break;
                        return;
                case 1:
                        DrawCircle (GetMousePosition ().x, GetMousePosition ().y, draw_size,
                                    draw_color);
                        DrawText ("Circle", 30, 1250, 20, font_color);

                        break;
                case 2:
                        DrawText ("Line", 30, 1250, 20, font_color);
                        if (IsMouseButtonDown (MOUSE_BUTTON_LEFT))
                                {
                                        DrawLine (draw_start_mouse.x, draw_start_mouse.y,
                                                  GetMousePosition ().x, GetMousePosition ().y,
                                                  draw_color);
                                }
                        break;

                case 3:
                        DrawText ("Poly", 30, 1250, 20, font_color);
                        for (int i = 0; i < poly_points_number; i++)
                                {
                                        DrawCircle (draw_poly_points[i].x, draw_poly_points[i].y,
                                                    1.0, draw_color);
                                }
                        break;
                case 4:
                        DrawText ("Text", 30, 1250, 20, font_color);
                        DrawText (TextFormat ("%c", draw_text), GetMousePosition ().x,
                                  GetMousePosition ().y, draw_size, draw_color);
                        break;
                case 5:
                        DrawText ("Rectangle", 30, 1250, 20, font_color);
                        if (IsMouseButtonDown (MOUSE_BUTTON_LEFT))
                                {
                                        DrawRectanglePoints (draw_start_mouse.x, draw_start_mouse.y,
                                                             GetMousePosition ().x,
                                                             GetMousePosition ().y, draw_color);
                                }
                        break;
                }

        DrawCircle (10, 1260, 10.0, draw_color);
}

void
save_file (FILE *fp)
{
        if (fp == NULL) // 一般不会遇见此场景
                {
                        fp = fopen ("new project.rpf", "wb");
                }
        rewind (fp);

        fwrite (&draw_board_index, sizeof (int), 1, fp);

        fwrite (draw_board, sizeof (struct draw), draw_board_index, fp);
}

void
load_file (FILE *fp)
{
        if (fp == NULL)
                return;

        rewind (fp);

        if (fread (&draw_board_index, sizeof (int), 1, fp) != 1)
                {
                        draw_board_index = 0;
                        return;
                }

        if (draw_board_index > 0)
                {
                        fread (draw_board, sizeof (struct draw), draw_board_index, fp);
                }

        TraceLog (LOG_INFO, "FILE: Loaded %d elements from file.", draw_board_index);
}
