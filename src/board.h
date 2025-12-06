#pragma once

#include "Graph_lib/Simple_window.h"
#include "score.h"


struct Window : Graph_lib::Window {

    Window(Graph_lib::Point xy, int w, int h, const std::string& title);

};

struct Board : Window {
    Board(Graph_lib::Point xy, int w, int h, const std::string& title);

    int handle(int key) override;

private:
    Score* score;
};