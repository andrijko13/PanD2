#include "Sprite.h"

namespace pand2 {
	PhysicsBody PhysicsBody::BodyWithCircleOfRadius(double radius) {
		PhysicsBody body;
		body.shape = PhysicsBodyCircle;
		body.radius = radius;

		return body;
	}

	Sprite::Sprite() : position(0.0,0.0), size(0.0,0.0) {

	}

	Sprite::~Sprite() {

	}
}
