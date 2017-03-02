#ifndef AJENGINE_DEFINE
#define AJENGINE_DEFINE
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Sprite.h"

namespace pand2 {

    class Engine {
        public:
            Engine(int, int);
            ~Engine();
        private:
            Graph   *graph;
            Sprite **nodes;

            void update();
    };

}

#endif
