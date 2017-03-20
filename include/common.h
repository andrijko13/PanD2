#ifndef AJCOMMON_DEFINE
#define AJCOMMON_DEFINE

#include <ajx/vec2d.h>

namespace pand2 {
	typedef ajx::vec2d<double> AJSize;
	typedef ajx::vec2d<double> AJPosition;
	typedef ajx::vec2d<double> AJForce;
	typedef ajx::vec2d<double> AJVelocity;
	typedef ajx::vec2d<double> AJImpulse;

	AJSize AJSizeMake(double width, double height);
	AJPosition AJPositionMake(double x, double y);
	AJForce AJForceMake(double dx, double dy);
	AJVelocity AJVelocityMake(double dx, double dy);
	AJImpulse AJImpulseMake(double dx, double dy);
}

#endif