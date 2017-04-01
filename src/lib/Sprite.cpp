#include "Sprite.h"

namespace pand2 {
	PhysicsBody PhysicsBody::BodyWithCircleOfRadius(double radius) {
		PhysicsBody body;
		body.shape = PhysicsBodyCircle;
		body.radius = radius;

		return body;
	}

	Sprite::Sprite() : position(0.0,0.0), size(0.0,0.0), name(""), dynamic(true) {

	}

	Sprite::~Sprite() {

	}

	void Sprite::applyForce(const Force &f) {
		userForce += f;
	}
    void Sprite::applyImpulse(const Impulse &i) {
    	userImpulse += i;
    }
    void Sprite::clearForce() {
    	userForce = ForceMake(0.0,0.0);
   	}
   	void Sprite::clearImpulse() {
    	userForce = ImpulseMake(0.0,0.0);
    }


}
