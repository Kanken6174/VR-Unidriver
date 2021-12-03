#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclure les en-têtes Windows rarement utilisés
namespace rots {
	struct Vector;
	struct Quaternion;

	Quaternion rotate(Quaternion q, Vector v);
	Quaternion multiplyQuaternions(Quaternion q1, Quaternion q2);
	Quaternion currentOrientation(Quaternion previousOrientation, Quaternion change, float duration);
	Quaternion changeSincePrevious(Quaternion previousOrientation, Vector angularVelocity, int stepSize /*, gradient*/);
}