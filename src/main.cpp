#include <iostream>
#include "Graph_lib/Graph.h"
#include "board.h"
#include <random>

void initialize_board() {
    Board board{Graph_lib::Point(100, 100), 800, 620, "Tetris"};
    Graph_lib::gui_main();
}

int main () {
    try {

        initialize_board();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Oops, something went wrong..." << std::endl;
        return 2;
    }
}