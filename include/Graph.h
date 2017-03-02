#ifndef AJGRAPH_DEFINE
#define AJGRAPH_DEFINE
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

namespace pand2 {

    class Graph {
        public:
            Graph(int, int);
            ~Graph();
        private:
            int width, height;

    };

}

#endif
