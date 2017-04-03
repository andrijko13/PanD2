#include "Engine.h"

namespace pand2 {

	Engine::Engine(int w, int h) : 	width(w),
								    height(h),
								    shouldUpdate(false),
								    frequency(pand2_update_freq),
								    gravityVector(0.0,-.098),
								    gravityEnabled(true),
								    treatBorderAsWall(true) {

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

    Engine::OutOfBoundsType Engine::outOfBounds(const Position &pos, const SpritePtr s) const {
    	//const Position pos = posi + PositionMake(ajx::epsilon, ajx::epsilon);
    	double radius  = s->physicsBody.radius;

    	if ((pos.x() - radius - ajx::epsilon) < 0) return OutOfBoundsLeft;
    	if ((pos.y() - radius - ajx::epsilon) < 0) return OutOfBoundsDown;
    	if ((pos.x() + radius + ajx::epsilon) > width) return OutOfBoundsRight;
    	if ((pos.y() + radius + ajx::epsilon) > height) return OutOfBoundsUp;
    	return OutOfBoundsNot;
    }

    Velocity Engine::_flipVel(const Velocity &v, const OutOfBoundsType &t) const {
    	switch (t) {
    		case OutOfBoundsLeft:
    		case OutOfBoundsRight:
    			return VelocityMake(-1*v.x(), v.y());
    			break; // here for good practice :) delete this line and u will get bad luck for 8 years
    		case OutOfBoundsUp:
    		case OutOfBoundsDown:
    			return VelocityMake(v.x(), -1*v.y());
    			break;
    		default:
    			return VelocityMake(v.x(), v.y());
    			break;
    	}
    	return VelocityMake(v.x(), v.y()); // once again, good practice
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
			OutOfBoundsType oobType = OutOfBoundsNot;
			if ((oobType = outOfBounds(newPosition, s))) {
				// collision

				if (treatBorderAsWall) {
					s->vel = s->physicsBody.restitution * _flipVel(s->vel, oobType);
				}

				if (s->vel.length() < pand2_bounce_min) {
					s->vel = VelocityMake(0.0,0.0); // moving too slow to bounce
				}

				//std::cout << "Collision: " << accel.y() << std::endl;
			} else {
				s->position = newPosition;

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