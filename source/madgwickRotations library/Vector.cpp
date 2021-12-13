#pragma once

#include "Vector.h"
#include "Quaternion.h"

using namespace madgwickRotations;

Quaternion Vector::toQuaternion() {
	return Quaternion(x, y, z, 0);
}