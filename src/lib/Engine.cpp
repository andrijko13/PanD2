#include "Engine.h"

namespace pand2 {

	Engine::Engine(int w, int h) : 	width(w),
								    height(h),
								    shouldUpdate(false),
								    frequency(pand2_update_freq),
								    gravityVector(0.0,-.098),
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

    void Engine::setGravity(const Force &f) {
    	gravityVector = f;
    }

    bool Engine::verifyBounds(const Position &pos, const SpritePtr s) {
    	//const Position pos = posi + PositionMake(ajx::epsilon, ajx::epsilon);
    	double radius  = s->physicsBody.radius;

    	if ((pos.x() - radius - ajx::epsilon) < 0 || (pos.y() - radius - ajx::epsilon) < 0 || (pos.x() + radius + ajx::epsilon) > width || (pos.y() + radius + ajx::epsilon) > height) return false;
    	return true;
    }

	void Engine::updatePhysics(const double &elapsed) {
		for (SpritePtr &s: nodes) {
			// process physics for each node
			if (!s->dynamic) continue;


			// handle forces
			Force net = s->userForce;
			if (gravityEnabled) net += gravityVector;
			Acceleration accel = net / s->physicsBody.mass;

			s->vel += (elapsed * accel); // v = at

			s->vel += (s->userImpulse / s->physicsBody.mass);

			// calculate new position
			Position newPosition = (s->position + (elapsed * s->vel));
			if (verifyBounds(newPosition, s)) {
				s->position = newPosition;
			} else {
				// collision
				s->vel = VelocityMake(0.0,0.0); // should impulse away

				//std::cout << "Collision: " << accel.y() << std::endl;
			}

			s->userForce = ForceMake(0.0,0.0);
			s->userImpulse = ImpulseMake(0.0,0.0);
		}
	}

	void Engine::update() {
		// calculate 1/hz so that we don't have to do it every iteration
		double updateTimeInterval = 1.0 / frequency;

		// actual update loop
		while (shouldUpdate) {

			//calculate elapsed time
			clock_t current = clock();
		    double elapsed = ((float)(current - lastUpdateTime)) * 1000 / CLOCKS_PER_SEC; // holds number of seconds as float

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