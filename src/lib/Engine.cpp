#include "Engine.h"

using namespace pand2;

Engine::Engine(int w, int h) {
    Graph *g = new Graph(w,h);
    this->graph = g;

    this->nodes = NULL;
}

Engine::~Engine() {
    delete this->graph;
    this->graph = NULL;

    this->nodes = NULL;
}

void Engine::update() {
    // run update loop
}
