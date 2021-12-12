#pragma once
#include <ctime>

namespace madgwickRotations {
	struct Vector;
	struct Quaternion;

	class MadgwickRotator;

	Quaternion rotate(Quaternion q, Vector v);
	Quaternion multiplyQuaternions(Quaternion q1, Quaternion q2);
	Quaternion addQuaternions(Quaternion q1, Quaternion q2);
}