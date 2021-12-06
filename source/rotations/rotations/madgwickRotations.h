#pragma once
#include <ctime>

namespace madgwickRotations {
	struct Vector;
	struct Quaternion;

	Quaternion rotate(Quaternion q, Vector v);
	Quaternion multiplyQuaternions(Quaternion q1, Quaternion q2);
	Quaternion addQuaternions(Quaternion q1, Quaternion q2);
	Quaternion currentOrientation(Quaternion previousOrientation, Quaternion change, time_t duration);
	Quaternion changeSincePrevious(Quaternion previousOrientation, Vector angularVelocity /*double stepSize, gradient*/ );
	Quaternion updateOrentation(Quaternion previousOrientation, Vector angularVelocity, time_t duration);
}