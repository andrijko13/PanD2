#include "Engine.h"

pand2::Engine::Engine(int w, int h) {
    pand2::Graph *g = new Graph(w,h);
    this->graph = g;

    this->nodes = NULL;
}

pand2::Engine::~Engine() {
    delete this->graph;
    this->graph = NULL;

    this->nodes = NULL;
}

void pand2::Engine::update() {
    // run update loop
}
