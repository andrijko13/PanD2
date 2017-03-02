#ifndef AJENGINE_DEFINE
#define AJENGINE_DEFINE
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Sprite.h"

namespace pand2 {

    class AJEngine {
        public:
            AJEngine(int, int);
            ~AJEngine();
        private:
            AJGraph   *graph;
            AJSprite **nodes;

            void update();
    };

}

#endif
