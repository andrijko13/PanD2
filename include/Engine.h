#ifndef AJENGINE_DEFINE
#define AJENGINE_DEFINE
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
//#include <function>
#include <time.h>

#include "Graph.h"
#include "Sprite.h"

namespace pand2 {

    class Engine { // TODO mark functions as const!!!
        public:
            Engine(int, int);
            ~Engine();

            void start() {shouldUpdate = true;};
            void pause() {shouldUpdate = false; updateThread.join();};
            void registerUpdateLoop(std::function <void (time_t)>func);
            void addBitmap(const char *bitfield);
        private:
        	// Declaration of private data strutures

        	typedef struct bitmap {
        		char *bitfield;
        	} Bitmap;

        	// private instance variables

        	std::thread updateThread;

            std::vector<Sprite> nodes;
            Bitmap map;

            time_t lastUpdateTime;
            std::function <void (time_t)> userUpdate;

            int width;
            int height;

            bool shouldUpdate;

            // private functions

            void update();
    };

}

#endif
