#include "Quaternion.h"

using namespace madgwickRotations;

Quaternion Quaternion::conjuguate() {
	return Quaternion(x, -y, -z, -w);
}

double Quaternion::magnitude() {
	return x * x + y * y + z * z + w * w;
}

Quaternion Quaternion::reciprocal() {
	return conjuguate().multiplyByReal(1/magnitude());
}

Quaternion Quaternion::multiplyByReal(double f) {
	return Quaternion(x * f, y * f, z * f, w * f);
}