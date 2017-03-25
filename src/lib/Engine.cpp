#include "Engine.h"

using namespace pand2;

Engine::Engine(int w, int h) : width(w), height(h), shouldUpdate(false) {
	map.bitfield = new char[w*h];
}

Engine::~Engine() {
	delete[] map.bitfield;
	if (updateThread.joinable()) updateThread.join();
}

void Engine::update() {
	while (shouldUpdate) {
		time_t current = time(NULL);
	    double elapsed = difftime(current, lastUpdateTime) * 1000;
    	userUpdate(lastUpdateTime);
	}
}

void Engine::registerUpdateLoop(std::function <void (time_t)>func) {
	userUpdate = func;
	this->updateThread = std::thread(&Engine::update, this);
}
