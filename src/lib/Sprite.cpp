#include "Sprite.h"

using namespace pand2;

PhysicsBody PhysicsBody::BodyWithCircleOfRadius(double radius) {
	PhysicsBody body;
	body.shape = PhysicsBodyCircle;
	body.radius = radius;

	return body;
}

Sprite::Sprite() {
	this->position = ajx::vec2d<double>::VectorWith(0.0,0.0);
}

Sprite::~Sprite() {

}
