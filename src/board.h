#pragma once

#include "Graph_lib/Simple_window.h"
#include "score.h"
#include "figure.h"
#include "constants.h"

struct Window : Graph_lib::Window {

    Window(Graph_lib::Point xy, int w, int h, const std::string& title);

};


struct Board : Window {
    Board(Graph_lib::Point xy, int w, int h, const std::string& title);

    bool is_game_over = false;

    int handle(int key) override;
    void update_by_time();
    void hide_current_figure();
    void show_current_figure();
    void add_new_figure();
    void game_over();
    bool check_game_over();
    void check_filled_raws();
    void update_field();
    void show_next_figure();

    void debug_field();
private:
    Graph_lib::Rectangle* filledPixels[board_width][board_length];
    Graph_lib::Rectangle* next_figure_pixels[4][4];
    bool filled[board_width][board_length];
    Score* score;
    Figure* current_figure;
    Figure* next_figure;

    void draw_pixels();
};