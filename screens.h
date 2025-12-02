#ifndef SCREENS_H
#define SCREENS_H

#include "raylib.h"
// define mode
typedef enum
{
        MENU,
        DRAW,
        FILE,
        EXIT,
} Mode;
// draw
struct draw
{
        char draw_board_type;
        int parameter[5];
        Vector2 position[10];
        Color draw_board_color;
};
extern int draw_board_index;
extern struct draw draw_board[10000];
extern Color draw_color;
extern int draw_size;
// font
extern Color font_color;
extern int font_size;
// function

void init_menu ();
void update_mode_menu ();
Mode return_mode_menu ();
void draw_menu ();

void init_draw ();
Mode return_mode_draw ();
void update_mode_draw ();
void draw_draw ();
#endif
