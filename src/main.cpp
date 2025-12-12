#include <iostream>
#include "Graph_lib/Graph.h"
#include "board.h"
#include "constants.h"

void initialize_board() {
    Board board{Graph_lib::Point(100, 100), board_width * pixel_size + 300, board_length * pixel_size + 10, "Tetris"};
    Graph_lib::gui_main();
}

int main () {
    try {
        std::srand(time(nullptr));
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