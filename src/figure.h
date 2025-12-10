#pragma once

#include "pixel.h"
#include "constants.h"

struct Figure {
    Figure();
    int get_color();
    int get_pixel_col(int pixel_num);
    int get_pixel_row(int pixel_num);
    bool can_move_left(bool filled[board_width][board_length]);
    bool can_move_right(bool filled[board_width][board_length]);
    bool can_move_down(bool filled[board_width][board_length]);
    bool can_rotate(bool filled[board_width][board_length],int afterotate[4][2]);
    void move_down();
    void move_left();
    void move_right();
    // void rotate_cw();
    void rotate_acw(bool filled[board_width][board_length]);

private:
    Pixel pixels[4];
    int type;
    int color;
};