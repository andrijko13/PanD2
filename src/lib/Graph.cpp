#include "Graph.h"

AJGraph::AJGraph(int w, int h) {
    this->width = w;
    this->height = h;
}

AJGraph::~AJGraph() {
    this->width = 0;
    this->height = 0;
}
