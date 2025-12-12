#include "board.h"
#include "score.h"
#include "Graph_lib/Simple_window.h"
#include "iostream"

Window::Window(Graph_lib::Point xy, int w, int h, const std::string &title)
        : Graph_lib::Window{xy, w, h, title} {

}

void repeated(void *p) {
    Board* board = ((Board*)p);
    if (board->check_game_over() || board->is_game_over) {
        board->is_game_over = true;
        board->game_over();
        return;
    }
    board->update_by_time();
    Fl::add_timeout(0.5, repeated, p);
}

Board::Board(Graph_lib::Point xy, int w, int h, const std::string &title) : Window(xy, w, h, title) {
    auto background = new Graph_lib::Rectangle(Graph_lib::Point(0, 0), w, h);
    background->set_fill_color(Graph_lib::Color::dark_cyan);
    this->attach(*background);

    auto field_border = new Graph_lib::Rectangle(Graph_lib::Point(5, 5), pixel_size * board_width + 4, pixel_size * board_length + 4);
    field_border->set_color(Graph_lib::Color::blue);
    auto border_style = Graph_lib::Line_style(Graph_lib::Line_style::Line_style_type::solid, 4);
    field_border->set_style(border_style);
    this->attach(*field_border);

    int field_width = pixel_size * board_width + 4;
    int new_figure_border_x = std::round(field_width + (w - field_width) / 2 - pixel_size * 3);
    int new_figure_border_y = std::round(h * 3 / 4 - pixel_size * 3);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            auto pixel = new Graph_lib::Rectangle(Graph_lib::Point(
                    new_figure_border_x + pixel_size * (i + 1), new_figure_border_y + pixel_size * (j + 1)
                    ), pixel_size, pixel_size);
            pixel->set_fill_color(Graph_lib::Color::red);
            pixel->set_color(Graph_lib::Color::dark_cyan);
            next_figure_pixels[i][j] = pixel;
            this->attach(*pixel);
        }
    }

    this->score = new Score();
    this->attach(*score->text_obj);

    for (int i = 0; i < board_width; i++) {
        for (int j = 0; j < board_length; j++) {
            filled[i][j] = false;
            auto c = Graph_lib::Color(Graph_lib::Color::dark_cyan);
            auto pixel = new Graph_lib::Rectangle(Graph_lib::Point(pixel_size * i + 6, pixel_size * j + 6),
                                                 pixel_size, pixel_size);
            pixel->set_fill_color(c);
            pixel->set_color(Graph_lib::Color::dark_cyan);
            filled_pixels[i][j] = pixel;
            this->attach(*pixel);
        }
    }

    this->current_figure = new Figure();
    for (int i = 0; i < 4; i++) {
        this->filled_pixels[current_figure->get_pixel_col(i)][current_figure->get_pixel_row(i)]->
                set_fill_color(Graph_lib::Color(current_figure->get_color()));
    }
    this->next_figure = new Figure();
    this->show_next_figure();

    Fl::add_timeout(1.0, repeated, this);
}

int Board::handle(int key) {
    if (key == FL_KEYDOWN) {
        int key_code = Fl::event_key();
        if (!is_game_over || key_code == FL_Escape) {
            switch (key_code) {
                case FL_Left: {
                    std::cout << "left\n";
                    if (current_figure->can_move_left(this->filled)) {
                        this->hide_current_figure();
                        current_figure->move_left();
                        this->show_current_figure();
                        Fl::redraw();
                    }
                    break;
                }
                case FL_Right: {
                    std::cout << "right\n";
                    if (current_figure->can_move_right(this->filled)) {
                        this->hide_current_figure();
                        current_figure->move_right();
                        this->show_current_figure();
                        Fl::redraw();
                    }
                    break;
                }
                case FL_Up: {
                    std::cout << "up\n";
                    this->hide_current_figure();
                    current_figure->rotate(this->filled);
                    this->show_current_figure();
                    Fl::redraw();
                    break;
                }
                case FL_Down: {
                    std::cout << "down\n";
                    if (current_figure->can_move_down(this->filled)) {
                        this->hide_current_figure();
                        current_figure->move_down();
                        this->show_current_figure();
                    }
                    update_field();
                    Fl::redraw();
                    break;
                }
                case 32: { // Space
                    std::cout << "space\n";
                    this->hide_current_figure();
                    while (current_figure->can_move_down(this->filled)) {
                        current_figure->move_down();
                    }
                    this->show_current_figure();
                    update_field();
                    break;
                }
                case FL_Escape: {
                    exit(0);
                    break;
                }
            }
            check_filled_raws();
        }
    }
    return key;
}

void Board::show_current_figure() {
    for (int i = 0; i < 4; i++) {
        filled_pixels[current_figure->get_pixel_col(i)][current_figure->get_pixel_row(i)]->set_fill_color(
                current_figure->get_color());
    }
}

void Board::hide_current_figure() {
    for (int i = 0; i < 4; i++) {
        filled_pixels[current_figure->get_pixel_col(i)][current_figure->get_pixel_row(i)]->set_fill_color(
                Graph_lib::Color::dark_cyan);
    }
}

void Board::check_filled_raws() {
    for (int i = 0; i < board_length; i++) {
        bool row_filled = true;
        for (int j = 0; j < board_width; j++) {
            if (!filled[j][i]) {
                row_filled = false;
                break;
            }
        }
        if (row_filled) {
            for (int col = 0; col < board_width; col++) {
                filled[col][i] = false;
                filled_pixels[col][i]->set_fill_color(Graph_lib::Color::dark_cyan);
            }
            for (int row = i; row > 0; row--) {
                for (int col = 0; col < board_width; col++) {
                    filled[col][row] = filled[col][row-1];
                    filled_pixels[col][row]->set_fill_color(filled_pixels[col][row - 1]->fill_color());
                }
            }
            this->score->add_score(100); // TODO Some more interesting logic
            Fl::redraw();
        }
    }
}

void Board::update_by_time() {
    if (current_figure->can_move_down(this->filled)) {
        this->hide_current_figure();
        current_figure->move_down();
        this->show_current_figure();
        Fl::redraw();
    }
    update_field();
}

void Board::add_new_figure() {
    for (int i = 0; i < 4; i++) {
        filled[current_figure->get_pixel_col(i)][current_figure->get_pixel_row(i)] = true;
    }
    check_filled_raws();
    for (int i = 0; i < 4; i++) {
        if (this->filled_pixels[next_figure->get_pixel_col(i)][next_figure->get_pixel_row(i)]->fill_color().as_int() != Graph_lib::Color::dark_cyan) {
            this->is_game_over = true;
            return;
        }
    }
    current_figure = next_figure;
    this->show_current_figure();
    Fl::redraw();
    next_figure = new Figure();
    this->show_next_figure();
}

void Board::update_field() {
    if (!this->current_figure->can_move_down(this->filled)) {
        add_new_figure();
    }
}

void Board::show_next_figure() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->next_figure_pixels[i][j]->set_fill_color(Graph_lib::Color::dark_cyan);
        }
    }
    int col_dif = next_figure->get_type() == 3 ? figure_spawn_col - 1 : figure_spawn_col - 2;
    for (int i = 0; i < 4; i++) {
        this->next_figure_pixels[next_figure->get_pixel_col(i) - col_dif][next_figure->get_pixel_row(i) + 1]->set_fill_color(next_figure->get_color());
    }
    Fl::redraw();
}

bool Board::check_game_over(){
    for (int i = 0; i < board_width; i++){
        if (filled[i][0]){
            return true;
        }
    }
    return false;
}

void Board::game_over(){
    fl_alert("Game over!");
    exit(0);
}

void Board::debug_field() {
    for (int k = 0; k < board_length; k++) {
        for (int l = 0; l < board_width; l++) {
            std::cout << filled_pixels[l][k]->fill_color().as_int() << " ";
        }
        std::cout << "\n";
    }
    std::cout << "Filled:\n";
    for (int k = 0; k < board_length; k++) {
        for (int l = 0; l < board_width; l++) {
            std::cout << filled[l][k] << " ";
        }
        std::cout << "\n";
    }
}
