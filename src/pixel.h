#pragma once

struct Pixel {
    int get_col();
    int get_row();
    void set_col(int new_col);
    void set_row(int new_row);
    void set_position(int new_col, int new_row);

private:
    int col;
    int row;
};
