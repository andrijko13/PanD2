#include "Sprite.h"

namespace pand2 {
	PhysicsBody PhysicsBody::BodyWithCircleOfRadius(double radius) {
		PhysicsBody body;
		body.shape = PhysicsBodyCircle;
		body.radius = radius;
		body.restitution = 0.3;

		return body;
	}

	Sprite::Sprite() : position(0.0,0.0), size(0.0,0.0), name(""), dynamic(true) {

	}

	Sprite::~Sprite() {

	}

	void PhysicsBody::setRestitution(const double &r) {
		restitution = r;
		if (r > (1.0)) restitution = 1.0;
	}

	void PhysicsBody::setFriction(const double &f) {
		frictionCoeff = 1.0-f;
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
