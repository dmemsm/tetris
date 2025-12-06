#include "board.h"
#include "score.h"
#include "Graph_lib/Simple_window.h"
#include "iostream"

Window::Window(Graph_lib::Point xy, int w, int h, const std::string &title)
        : Graph_lib::Window{xy, w, h, title}
{
}

Board::Board(Graph_lib::Point xy, int w, int h, const std::string &title) : Window(xy, w, h, title) {
    auto rect = new Graph_lib::Rectangle(Graph_lib::Point(5, 5), 400-10, 600-10);
    rect->set_color(Graph_lib::Color::blue);
    this->attach(*rect);

    this->score = new Score();
    this->attach(*score->text_obj);
}

int Board::handle(int key) {
    if (key == FL_KEYDOWN) {
        switch (Fl::event_key()) {
            case FL_Left: {
                std::cout << "left\n";
                break;
            }
            case FL_Right: {
                std::cout << "right\n";
                break;
            }
            case FL_Up: {
                std::cout << "up\n";
                break;
            }
            case FL_Down: {
                std::cout << "down\n";
                break;
            }
            case 32: { // Space
                std::cout << "space\n";
                break;
            }
            case FL_Escape: {
                exit(0);
                break;
            }
        }
    }
}
