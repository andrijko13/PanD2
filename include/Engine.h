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

            void start() {shouldUpdate = true; lastUpdateTime = clock(); };
            void pause() {shouldUpdate = false; updateThread.join();};
            void registerUpdateLoop(std::function <void (double)>func);
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

            clock_t lastUpdateTime;
            std::function <void (double)> userUpdate;

            int width;
            int height;

            bool shouldUpdate;

            double frequency;
            double fps; // frames per second - should be calculated

            // private functions

            void update();
            void updatePhysics();
    };

}

#endif
