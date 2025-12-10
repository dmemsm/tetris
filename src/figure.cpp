#include "figure.h"
#include "Graph_lib/fltk.h"

#include "ctime"
#include "iostream"

Figure::Figure() {
    //std::srand(std::time(nullptr));
    this->color = rand() % 6;

    this->type = rand() % 7;
    int middle_col = 8;
    switch (this->type) {
        case 0: {
            // * * *
            //     *
            pixels[0].set_position(middle_col-1, 0);
            pixels[1].set_position(middle_col, 0);
            pixels[2].set_position(middle_col+1, 0);
            pixels[3].set_position(middle_col+1, 1);
            break;
        }
        case 1: {
            // * * *
            //   *
            pixels[0].set_position(middle_col-1, 0);
            pixels[1].set_position(middle_col+1, 0);
            pixels[2].set_position(middle_col, 0);
            pixels[3].set_position(middle_col, 1);
            break;
        }
        case 2: {
            // * * *
            // *
            pixels[0].set_position(middle_col-1, 0);
            pixels[1].set_position(middle_col, 0);
            pixels[2].set_position(middle_col+1, 0);
            pixels[3].set_position(middle_col-1, 1);
            break;
        }
        case 3: {
            // * * * *
            pixels[0].set_position(middle_col-1, 0);
            pixels[1].set_position(middle_col, 0);
            pixels[2].set_position(middle_col+1, 0);
            pixels[3].set_position(middle_col+2, 0);
            break;
        }
        case 4: {
            //   * *
            // * *
            pixels[0].set_position(middle_col, 0);
            pixels[1].set_position(middle_col+1, 0);
            pixels[2].set_position(middle_col, 1);
            pixels[3].set_position(middle_col-1, 1);
            break;
        }
        case 5: {
            // * *
            //   * *
            pixels[0].set_position(middle_col-1, 0);
            pixels[1].set_position(middle_col, 1);
            pixels[2].set_position(middle_col, 0);
            pixels[3].set_position(middle_col+1, 1);
            break;
        }
        case 6: {
            // * *
            // * *
            pixels[0].set_position(middle_col-1, 0);
            pixels[1].set_position(middle_col, 0);
            pixels[2].set_position(middle_col-1, 1);
            pixels[3].set_position(middle_col, 1);
            break;
        }
    }
}

int Figure::get_color() {
    return this->color;
}
int Figure::get_pixel_col(int pixel_num) {
    if (pixel_num > 3 || pixel_num < 0) {
        return 0;
    }
    return this->pixels[pixel_num].get_col();
}

int Figure::get_pixel_row(int pixel_num) {
    if (pixel_num > 3 || pixel_num < 0) {
        return 0;
    }
    return this->pixels[pixel_num].get_row();
}

void Figure::move_down() {
    for (int i = 0; i < 4; i++) {
        this->pixels[i].set_row(this->pixels[i].get_row() + 1);
    }
}

void Figure::move_left() {
    for (int i = 0; i < 4; i++) {
        this->pixels[i].set_col(this->pixels[i].get_col() - 1);
    }
}

void Figure::move_right() {
    for (int i = 0; i < 4; i++) {
        this->pixels[i].set_col(this->pixels[i].get_col() + 1);
    }
}

bool Figure::can_move_left(bool filled[board_width][board_length]) {
    for (int i = 0; i < 4; i++) {
        if (get_pixel_col(i) == 0) {
            return false;
        }
        if (filled[get_pixel_col(i)-1][get_pixel_row(i)]) {
            return false;
        }
    }
    return true;
}

bool Figure::can_move_right(bool filled[board_width][board_length]) {
    for (int i = 0; i < 4; i++) {
        if (get_pixel_col(i) == 15) {
            return false;
        }
        if (filled[get_pixel_col(i)+1][get_pixel_row(i)]) {
            return false;
        }
    }
    return true;
}

bool Figure::can_move_down(bool filled[board_width][board_length]) {
    for (int i = 0; i < 4; i++) {
        if (get_pixel_row(i) == 19) {
            return false;
        }
        if (filled[get_pixel_col(i)][get_pixel_row(i)+1]) {
            return false;
        }
    }
    return true;
}

// void Figure::rotate_cw() {
//     int afterrotate[4][2];
//     int pivr,pivc;
//     // We choose tiles[2] as pivot and rotate wrt it.
//     pivr = this->pixels[2].get_row();
//     pivc = this->pixels[2].get_col();

//     int coldiff[4];
//     int rowdiff[4];
//     for(int i=0;i<4;i++){
//         rowdiff[i] = pivr - this->pixels[i].get_row();
//         coldiff[i] = this->pixels[i].get_col() - pivc;
//     }
//     for(int i=0;i<4;i++)
//     {
//         afterrotate[i][0] = pivr + coldiff[i]; // new row
//         afterrotate[i][1] = pivc + rowdiff[i]; // new col
//     }
//     if(type!=6)
//     {
//         this->pixels[0].set_row(afterrotate[0][0]);
//         this->pixels[0].set_col(afterrotate[0][1]);
//         this->pixels[1].set_row(afterrotate[1][0]);
//         this->pixels[1].set_col(afterrotate[1][1]);
//         this->pixels[3].set_row(afterrotate[3][0]);
//         this->pixels[3].set_col(afterrotate[3][1]);
//     }
// }
bool Figure::can_rotate(bool filled[board_width][board_length], int afterrotate[4][2]){

    for (int i = 0; i < 4; i++){
        if ((afterrotate[i][0] < 0 || afterrotate[i][0] > board_width - 1) || filled[afterrotate[i][0]][afterrotate[i][1]] || (afterrotate[i][1] > board_length - 1 || afterrotate[i][1] < 0 )) {
            return false;
        }
    }
    return true;
}



void Figure::rotate_acw(bool filled[board_width][board_length]) {
    int afterrotate[4][2]; // first elem col, second elem row
    int rotate_col = this->pixels[2].get_col();
    int rotate_row = this->pixels[2].get_row();

    int coldiff[4];
    int rowdiff[4];
    for(int i=0;i<4;i++){
        rowdiff[i] = rotate_row - this->pixels[i].get_row();
        coldiff[i] = this->pixels[i].get_col() - rotate_col;
    }
    for(int i=0;i<4;i++)
    {
        afterrotate[i][0] = rotate_col - rowdiff[i]; // new col
        afterrotate[i][1] = rotate_row - coldiff[i]; // new row
    }
    

    if (can_rotate(filled,afterrotate)){
        if(type!=6)
        {
            for (int i = 0; i < 4; i++){
                if (i == 2) continue;
                this -> pixels[i].set_col(afterrotate[i][0]);
                this -> pixels[i].set_row(afterrotate[i][1]);

            }
            // this->pixels[0].set_col(afterrotate[0][0]);
            // this->pixels[0].set_row(afterrotate[0][1]);
            // this->pixels[1].set_col(afterrotate[1][0]);
            // this->pixels[1].set_row(afterrotate[1][1]);
            // this->pixels[3].set_col(afterrotate[3][0]);
            // this->pixels[3].set_row(afterrotate[3][1]);
        }
    }
}

