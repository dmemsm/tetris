#include "iostream"
#include "score.h"
#include "constants.h"

Score::Score() {
    text_obj = new Graph_lib::Text(Graph_lib::Point(pixel_size * board_width + 80, 100), "Current score: " + std::to_string(current_score));
    text_obj->set_font_size(24);
}

void Score::add_score(int score) {
    current_score += score;
    this->text_obj->set_label("Current score: " + std::to_string(this->current_score));
    Fl::redraw();
}