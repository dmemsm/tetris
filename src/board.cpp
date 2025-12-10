#include "board.h"
#include "score.h"
#include "Graph_lib/Simple_window.h"
#include "iostream"



Window::Window(Graph_lib::Point xy, int w, int h, const std::string &title)
        : Graph_lib::Window{xy, w, h, title}
{
}


void repeated(void *p) {
    ((Board*)p)->update_by_time();
    Fl::add_timeout(0.5, repeated, p);
}

Board::Board(Graph_lib::Point xy, int w, int h, const std::string &title) : Window(xy, w, h, title) {
    auto background = new Graph_lib::Rectangle(Graph_lib::Point(0, 0), w, h);
    background->set_fill_color(Graph_lib::Color::dark_cyan);
    this->attach(*background);
    auto rect = new Graph_lib::Rectangle(Graph_lib::Point(5, 5), pixel_size * board_width + 4, pixel_size * board_length + 4);
    rect->set_color(Graph_lib::Color::blue);
    auto style = Graph_lib::Line_style(Graph_lib::Line_style::Line_style_type::solid, 4);
    rect->set_style(style);
    this->attach(*rect);

    this->score = new Score();
    this->attach(*score->text_obj);

    for (int i = 0; i < board_width; i++) {
        for (int j = 0; board_length < board_length; j++) {
            filled[i][j] = false;
            Graph_lib::Color c = Graph_lib::Color(Graph_lib::Color::dark_cyan);
            auto pixel = new Graph_lib::Rectangle(Graph_lib::Point(pixel_size * i + 6, pixel_size * j + 6),
                                                 pixel_size, pixel_size);
            pixel->set_fill_color(c);
            pixel->set_color(Graph_lib::Color::dark_cyan);
            filledPixels[i][j] = pixel;
            this->attach(*pixel);
        }
    }

    this->current_figure = new Figure();
    for (int i = 0; i < 4; i++) {
        this->filledPixels[current_figure->get_pixel_col(i)][current_figure->get_pixel_row(i)]->
                set_fill_color(Graph_lib::Color(current_figure->get_color()));
    }
    this->next_figure = new Figure();

    Fl::add_timeout(1.0, repeated, this);

    //draw_pixels();
}

int Board::handle(int key) {
    if (key == FL_KEYDOWN) {
        switch (Fl::event_key()) {
            case FL_Left: {
                std::cout << "left\n";
                if (current_figure->can_move_left(this->filled)) {
                    this->delete_current_figure();
                    current_figure->move_left();
                    this->add_current_figure();
                    Fl::redraw();
                }
                break;
            }
            case FL_Right: {
                std::cout << "right\n";
                if (current_figure->can_move_right(this->filled)) {
                    this->delete_current_figure();
                    current_figure->move_right();
                    this->add_current_figure();
                    Fl::redraw();
                }
                break;
            }
            case FL_Up: {
                std::cout << "up\n";
                this->delete_current_figure();
                current_figure->rotate_acw();
                this->add_current_figure();
                Fl::redraw();
                break;
            }
            case FL_Down: {
                std::cout << "down\n";
                if (current_figure -> can_move_down(this -> filled)){
                    this->delete_current_figure();
                    current_figure->move_down();
                    this->add_current_figure();
                    Fl::redraw();
            }
                break;
            }
            case 32: { // Space
                //draw_pixels();
                std::cout << "space\n";
                this->delete_current_figure();
                while (current_figure->can_move_down(this->filled)) {
                    current_figure->move_down();
                }
                this->add_current_figure();
                Fl::redraw();
                break;
            }
            case FL_Escape: {
                exit(0);
                break;
            }
        }
    }
    return key;
}




void Board::draw_pixels() {
    for (int i = 0; i < board_width; i++) {
        for (int j = 0; j < board_length; j++) {
            filledPixels[i][j]->set_fill_color(Graph_lib::Color::dark_cyan);
        }
    }

    for (int i = 0; i < board_width; i++) {
        for (int j = 0; j < board_length; j++) {
            int r = rand();
            if (r % 2) {
                filledPixels[i][j]->set_fill_color(Graph_lib::Color(r % 256));
            }
        }
    }
    Fl::redraw();
}

void Board::delete_current_figure() {
    for (int i = 0; i < 4; i++) {
        filledPixels[current_figure->get_pixel_col(i)][current_figure->get_pixel_row(i)]->set_fill_color(
                Graph_lib::Color::dark_cyan);
    }
}

void Board::add_current_figure() {
    for (int i = 0; i < 4; i++) {
        filledPixels[current_figure->get_pixel_col(i)][current_figure->get_pixel_row(i)]->set_fill_color(
                current_figure->get_color());
    }
}

void Board::update_by_time() {
    if (current_figure->can_move_down(this->filled)) {
        this->delete_current_figure();
        current_figure->move_down();
        this->add_current_figure();
        Fl::redraw();
    } else {
        for (int i = 0; i < 4; i++) {
            filled[current_figure->get_pixel_col(i)][current_figure->get_pixel_row(i)] = true;
        }
        current_figure = next_figure;
        next_figure = new Figure();
    }
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
                filledPixels[col][i]->set_fill_color(Graph_lib::Color::dark_cyan);
            }
            for (int row = i; row > 0; row--) {
                for (int col = 0; col < board_width; col++) {
                    filled[col][row] = filled[col][row-1];
                    filledPixels[col][row]->set_fill_color(filledPixels[col][row-1]->fill_color());
                }
            }
            this->score->add_score(100); // TODO Some more interesting logic
        }
    }
}
