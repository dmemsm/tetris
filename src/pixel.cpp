#include "pixel.h"

int Pixel::get_col() {
    return this->col;
}

int Pixel::get_row() {
    return this->row;
}

void Pixel::set_col(int new_col) {
    this->col = new_col;
}

void Pixel::set_row(int new_row) {
    this->row = new_row;
}

void Pixel::set_position(int new_col, int new_row) {
    set_col(new_col);
    set_row(new_row);
}