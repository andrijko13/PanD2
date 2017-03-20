#include "common.h"

namespace pand2 {
	AJSize AJSizeMake(double width, double height) {
		return AJSize::VectorWith(width, height);
	}

	AJPosition AJPositionMake(double x, double y) {
		return AJPosition::VectorWith(x, y);
	}

	AJForce AJForceMake(double dx, double dy) {
		return AJForce::VectorWith(dx, dy);
	}

	AJVelocity AJVelocityMake(double dx, double dy) {
		return AJVelocity::VectorWith(dx, dy);
	}

	AJImpulse AJImpulseMake(double dx, double dy) {
		return AJImpulse::VectorWith(dx, dy);
	}
}