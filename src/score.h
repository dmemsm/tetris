#pragma once

#include "Graph_lib/Graph.h"

struct Score {

    Score();

    Graph_lib::Text* text_obj;

    void add_score(int score);
private:
    int current_score;

};
