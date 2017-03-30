#include "Engine.h"

using namespace pand2;

Engine::Engine(int w, int h) : width(w), height(h), shouldUpdate(false), frequency(70.0) {
	map.bitfield = new char[w*h];
}

Engine::~Engine() {
	delete[] map.bitfield;
	if (updateThread.joinable()) updateThread.join();
}

void Engine::updatePhysics() {

}

void Engine::update() {
	// calculate 1/hz so that we don't have to do it every iteration
	double updateTimeInterval = 1.0 / frequency;

	// actual update loop
	while (shouldUpdate) {

		//calculate elapsed time
		clock_t current = clock();
	    double elapsed = ((float)(current - lastUpdateTime)) * 1000 / CLOCKS_PER_SEC;

	    // run update if frame complete
	    if (elapsed >= updateTimeInterval) {
	    	updatePhysics();
	    	userUpdate(elapsed);
	    	lastUpdateTime = current;
	    }
	}
}

void Engine::registerUpdateLoop(std::function <void (double)>func) {
	userUpdate = func;
	this->updateThread = std::thread(&Engine::update, this);
}
