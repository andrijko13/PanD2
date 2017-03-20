#include "Sprite.h"

namespace pand2 {
	PhysicsBody PhysicsBody::BodyWithCircleOfRadius(double radius) {
		PhysicsBody body;
		body.shape = PhysicsBodyCircle;
		body.radius = radius;

		return body;
	}

	Sprite::Sprite() {
		this->position = AJPosition::VectorWith(0.0,0.0);
	}

	Sprite::~Sprite() {

	}
}
