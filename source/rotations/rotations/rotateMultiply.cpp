#pragma once

#include "Quaternions.h"
#include "Vector.h"
#include "framework.h"

rots::Quaternion rots::rotate(Quaternion q, Vector v) {
	rots::Quaternion tmp = rots::multiplyQuaternions(q, v.toQuaternion());
	return multiplyQuaternions(tmp, q.inverse());
}