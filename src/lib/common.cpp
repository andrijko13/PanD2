#include "common.h"

namespace pand2 {
	Size SizeMake(double width, double height) {
		return Size::VectorWith(width, height);
	}

	Position PositionMake(double x, double y) {
		return Position::VectorWith(x, y);
	}

	Force ForceMake(double dx, double dy) {
		return Force::VectorWith(dx, dy);
	}

	Velocity VelocityMake(double dx, double dy) {
		return Velocity::VectorWith(dx, dy);
	}

	Acceleration AccelerationMake(double dx, double dy) {
		return Acceleration::VectorWith(dx, dy);
	}

	Impulse ImpulseMake(double dx, double dy) {
		return Impulse::VectorWith(dx, dy);
	}

	Inertia InertiaMake(double dx, double dy) {
		return Inertia::VectorWith(dx, dy);
	}
}