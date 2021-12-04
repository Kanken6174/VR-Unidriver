#include "Quaternion.h"
#include "Vector.h"
#include "rotations.h"

using namespace rotations;

Quaternion rotations::rotate(Quaternion q, Vector v) {
	Quaternion tmp = multiplyQuaternions(q, v.toQuaternion());
	return multiplyQuaternions(tmp, q.reciprocal());
}

Quaternion rotations::multiplyQuaternions(Quaternion q1, Quaternion q2) {
	return Quaternion(
		q1.getX() * q2.getX() - q1.getY() * q2.getY() - q1.getZ() * q2.getZ() - q1.getW() * q2.getW(),
		q1.getY() * q2.getX() + q1.getX() * q2.getY() + q1.getZ() * q2.getW() - q1.getW() * q2.getZ(),
		q1.getX() * q2.getZ() - q1.getY() * q2.getW() + q1.getZ() * q2.getX() + q1.getW() * q2.getY(),
		q1.getX() * q2.getW() + q1.getY() * q2.getZ() + q1.getZ() * q2.getY() + q1.getW() * q2.getX()
	);
}

Quaternion rotations::addQuaternions(Quaternion q1, Quaternion q2) {
	return Quaternion(
		q1.getX() + q2.getX(),
		q1.getY() + q2.getY(),
		q1.getZ() + q2.getZ(),
		q1.getW() + q2.getW()
	);
}

Quaternion rotations::currentOrientation(Quaternion previousOrientation, Quaternion change, float duration) {
	return addQuaternions(previousOrientation, change).multiplyByReal(duration);
}

Quaternion rotations::changeSincePrevious(Quaternion previousOrientation, Vector angularVelocity /*float stepSize, gradient*/ ) {
	Quaternion tmp = multiplyQuaternions(previousOrientation, angularVelocity.toQuaternion());
	return multiplyQuaternions(tmp, previousOrientation.reciprocal());
}

Quaternion updateOrentation(Quaternion previousOrientation, Vector angularVelocity, float duration) {
	Quaternion change = changeSincePrevious(previousOrientation, angularVelocity);
	return currentOrientation(previousOrientation, change, duration);	
}