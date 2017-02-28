#include "Engine.h"

AJEngine::AJEngine(int w, int h) {
    AJGraph *g = new AJGraph(w,h);
    this->graph = g;

    this->nodes = NULL;
}

AJEngine::~AJEngine() {
    delete this->graph;
    this->graph = NULL;

    this->nodes = NULL;
}

void AJEngine::update() {
    // run update loop
}
