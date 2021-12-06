#include "Quaternion.h"
#include "Vector.h"
#include "madgwickRotations.h"

using namespace madgwickRotations;

Quaternion madgwickRotations::rotate(Quaternion q, Vector v) {
	Quaternion tmp = multiplyQuaternions(q, v.toQuaternion());
	return multiplyQuaternions(tmp, q.reciprocal());
}

Quaternion madgwickRotations::multiplyQuaternions(Quaternion q1, Quaternion q2) {
	return Quaternion(
		q1.getX() * q2.getX() - q1.getY() * q2.getY() - q1.getZ() * q2.getZ() - q1.getW() * q2.getW(),
		q1.getY() * q2.getX() + q1.getX() * q2.getY() + q1.getZ() * q2.getW() - q1.getW() * q2.getZ(),
		q1.getX() * q2.getZ() - q1.getY() * q2.getW() + q1.getZ() * q2.getX() + q1.getW() * q2.getY(),
		q1.getX() * q2.getW() + q1.getY() * q2.getZ() + q1.getZ() * q2.getY() + q1.getW() * q2.getX()
	);
}

Quaternion madgwickRotations::addQuaternions(Quaternion q1, Quaternion q2) {
	return Quaternion(
		q1.getX() + q2.getX(),
		q1.getY() + q2.getY(),
		q1.getZ() + q2.getZ(),
		q1.getW() + q2.getW()
	);
}

Quaternion madgwickRotations::currentOrientation(Quaternion previousOrientation, Quaternion change, time_t duration) {
	return addQuaternions(previousOrientation, change).multiplyByReal(duration);
}

Quaternion madgwickRotations::changeSincePrevious(Quaternion previousOrientation, Vector angularVelocity /*double stepSize, gradient*/ ) {
	Quaternion tmp = multiplyQuaternions(previousOrientation, angularVelocity.toQuaternion());
	return multiplyQuaternions(tmp, previousOrientation.reciprocal());
}

Quaternion updateOrentation(Quaternion previousOrientation, Vector angularVelocity, time_t duration) {
	Quaternion change = changeSincePrevious(previousOrientation, angularVelocity);
	return currentOrientation(previousOrientation, change, duration);	
}