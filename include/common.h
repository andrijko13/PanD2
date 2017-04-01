#ifndef AJCOMMON_DEFINE
#define AJCOMMON_DEFINE

#include <ajx/vec2d.h>

namespace pand2 {
	typedef ajx::vec2d<double> Size;
	typedef ajx::vec2d<double> Position;
	typedef ajx::vec2d<double> Force;
	typedef ajx::vec2d<double> Velocity;
	typedef ajx::vec2d<double> Acceleration;
	typedef ajx::vec2d<double> Impulse;
	typedef ajx::vec2d<double> Inertia;

	Size SizeMake(double width, double height);
	Position PositionMake(double x, double y);
	Force ForceMake(double dx, double dy);
	Velocity VelocityMake(double dx, double dy);
	Acceleration AccelerationMake(double dx, double dy);
	Impulse ImpulseMake(double dx, double dy);
	Inertia InertiaMake(double dx, double dy);
}

#endif