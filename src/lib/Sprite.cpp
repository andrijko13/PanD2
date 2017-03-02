#include "Sprite.h"

pand2::PhysicsBody pand2::PhysicsBody::BodyWithCircleOfRadius(double radius) {
	pand2::PhysicsBody body;
	body.shape = PhysicsBodyCircle;
	body.radius = radius;

	return body;
}

pand2::Sprite::Sprite() {

}

pand2::Sprite::~Sprite() {

}
