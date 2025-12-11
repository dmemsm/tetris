#pragma once

#include "pixel.h"
#include "constants.h"

struct Figure {
    Figure();
    int get_color() const;
    int get_pixel_col(int pixel_num);
    int get_pixel_row(int pixel_num);
    int get_type() const;
    bool can_move_left(bool filled[board_width][board_length]);
    bool can_move_right(bool filled[board_width][board_length]);
    bool can_move_down(bool filled[board_width][board_length]);
    void move_down();
    void move_left();
    void move_right();
    void rotate(bool filled[board_width][board_length]);
    static bool can_rotate(bool filled[board_width][board_length], int after_rotate[4][2]);

private:
    Pixel pixels[4];
    int type;
    int color;
};