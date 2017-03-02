#include "Graph.h"

pand2::Graph::Graph(int w, int h) {
    this->width = w;
    this->height = h;
}

pand2::Graph::~Graph() {
    this->width = 0;
    this->height = 0;
}
