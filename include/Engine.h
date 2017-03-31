#ifndef AJENGINE_DEFINE
#define AJENGINE_DEFINE
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <string>
#include <time.h>

#include "Graph.h"
#include "Sprite.h"

namespace pand2 {

    class Engine { // TODO mark functions as const!!!
        public:

            const double pand2_update_freq = 70.0;

            Engine(int, int);
            ~Engine();

            void addSprite(SpritePtr sprite);
            void removeAllSprites();
            void removeSpriteWithName(const std::string &name);

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

            std::vector<SpritePtr> nodes;
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
            void updatePhysics(const double &elspased);
    };

}

#endif
