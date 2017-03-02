#ifndef AJGRAPH_DEFINE
#define AJGRAPH_DEFINE
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

namespace pand2 {

    class AJGraph {
        public:
            AJGraph(int, int);
            ~AJGraph();
        private:
            int width, height;

    };

}

#endif
