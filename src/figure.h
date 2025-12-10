#pragma once

#include "pixel.h"

struct Figure {
    Figure();
    int get_color();
    int get_pixel_col(int pixel_num);
    int get_pixel_row(int pixel_num);
    bool can_move_left(bool filled[16][20]);
    bool can_move_right(bool filled[16][20]);
    bool can_move_down(bool filled[16][20]);
    void move_down();
    void move_left();
    void move_right();
    void rotate_cw();
    void rotate_acw();


private:
    Pixel pixels[4];
    int type;
    int color;
};