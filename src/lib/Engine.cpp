#include "Engine.h"

namespace pand2 {

	Engine::Engine(int w, int h) : 	width(w),
								    height(h),
								    shouldUpdate(false),
								    frequency(pand2_update_freq),
								    gravityVector(0.0,-9.8),
								    gravityEnabled(true) {

		map.bitfield = new char[w*h];
	}

	Engine::~Engine() {
		delete[] map.bitfield;
		if (updateThread.joinable()) updateThread.join();
	}

	void Engine::addSprite(SpritePtr sprite) {
		nodes.push_back(sprite);
	}
    void Engine::removeAllSprites() {
    	nodes.clear();
    }
    void Engine::removeSpriteWithName(const std::string &name) {
   		// todo
    }

    bool Engine::verifyBounds(const Position &pos, const SpritePtr s) {
    	Position spos = s->position;
    	double radius  = s->physicsBody.radius;

    	if (spos.x() - radius < 0 || spos.y() - radius < 0 || spos.x() + radius > width || spos.y() + radius > height) return false;
    	return true;
    }

	void Engine::updatePhysics(const double &elapsed) {
		for (SpritePtr &s: nodes) {
			// process physics for each node
			if (!s->dynamic) continue;

			Force net = s->userForce;
			if (gravityEnabled) net += gravityVector;
			Acceleration accel = net / s->physicsBody.mass;

			s->vel += (elapsed * accel); // v = at
			Position newPosition = (elapsed * s->vel);
			if (verifyBounds(newPosition, s)) {
				s->position = newPosition;
			} else {
				std::cout << "Collision? " << std::endl;
			}

			s->userForce = ForceMake(0.0,0.0);
		}
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
		    	updatePhysics(elapsed);
		    	userUpdate(elapsed);
		    	lastUpdateTime = current;
		    }
		}
	}

	void Engine::registerUpdateLoop(std::function <void (double)>func) {
		userUpdate = func;
		this->updateThread = std::thread(&Engine::update, this);
	}

}