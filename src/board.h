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

    int handle(int key) override;
    void update_by_time();
    void delete_current_figure();
    void add_current_figure(); 

private:
    Graph_lib::Rectangle* filledPixels[board_width][board_length];
    bool filled[board_width][board_length];
    Score* score;
    Figure* current_figure;
    Figure* next_figure;

    void draw_pixels();
    //void draw() override;
};