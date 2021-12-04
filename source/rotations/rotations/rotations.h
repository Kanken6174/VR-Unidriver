#pragma once

namespace rotations {
	struct Vector;
	struct Quaternion;

	Quaternion rotate(Quaternion q, Vector v);
	Quaternion multiplyQuaternions(Quaternion q1, Quaternion q2);
	Quaternion addQuaternions(Quaternion q1, Quaternion q2);
	Quaternion currentOrientation(Quaternion previousOrientation, Quaternion change, float duration);
	Quaternion changeSincePrevious(Quaternion previousOrientation, Vector angularVelocity /*float stepSize, gradient*/ );
	Quaternion updateOrentation(Quaternion previousOrientation, Vector angularVelocity, float duration);
}