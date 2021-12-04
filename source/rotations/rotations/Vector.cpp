#pragma once

#include "Vector.h"
#include "Quaternion.h"

using namespace rotations;

Quaternion Vector::toQuaternion() {
	return Quaternion(x, y, z, 0);
}