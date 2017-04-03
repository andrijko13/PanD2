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
#include "common.h"

/*
 * The engine portion of the physics engine (i.e. the core)
 *
 * Some of the most important todo's and wishlist:
 *
 * Add determinism, perhaps? It would be nice to have engine with
 *    each frame being deterministic, so we can sync with server
 *    every x frames. Also that way we can run an update loop and
 *    queue results until they are ready to be displayed.
 *
 * This can be fiddled with after engine can perform robust
 *    simulation
 *
*/

namespace pand2 {

    class Engine { // TODO mark functions as const!!!
        public:

            // Declaration of data strutures

            typedef enum OutOfBoundsType {
                OutOfBoundsNot = 0,
                OutOfBoundsLeft,
                OutOfBoundsUp,
                OutOfBoundsRight,
                OutOfBoundsDown,
                OutOfBoundsTotal
            } OutOfBoundsType;

            typedef struct bitmap {
                char *bitfield;
            } Bitmap;

            // constants

            const double pand2_update_freq = 70.0;
            const double pand2_bounce_min  = 0.0001;

            // constructors

            Engine(int, int);
            ~Engine();

            // methods

            void setGravity(const Force &f);

            void addSprite(SpritePtr sprite);
            void removeAllSprites();
            void removeSpriteWithName(const std::string &name);

            void start() {shouldUpdate = true; lastUpdateTime = clock(); };
            void pause() {shouldUpdate = false; updateThread.join();};
            void registerUpdateLoop(std::function <void (double)>func);
            void addBitmap(const char *bitfield);

            bool treatBorderAsWall;
        private:

        	// private instance variables

        	std::thread updateThread;

            std::vector<SpritePtr> nodes;
            Bitmap map;

            clock_t lastUpdateTime;
            std::function <void (double)> userUpdate;

            int width;
            int height;

            bool shouldUpdate;
            bool gravityEnabled;
            Force gravityVector;

            double frequency;
            double fps; // frames per second - should be calculated

            // private functions

            void update();
            void updatePhysics(const double &elspased);

            OutOfBoundsType outOfBounds(const Position &pos, const SpritePtr s) const;

            // helper functions
            Velocity _flipVel(const Velocity &v, const OutOfBoundsType &t, const double &resti, const double &fric) const;
    };

}

#endif
