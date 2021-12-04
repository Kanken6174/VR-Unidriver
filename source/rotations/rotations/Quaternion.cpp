#include "Quaternion.h"
#include "rotations.h"

using namespace rotations;

Quaternion Quaternion::conjuguate() {
	return Quaternion(x, -y, -z, -w);
}

float Quaternion::magnitude() {
	return x * x + y * y + z * z + w * w;
}

Quaternion Quaternion::reciprocal() {
	return conjuguate().multiplyByReal(1/magnitude());
}

Quaternion Quaternion::multiplyByReal(float f) {
	return Quaternion(x * f, y * f, z * f, w * f);
}