/**
 * @file madgwickRotations.cpp
 * @author Elliott Le Guéhennec (elliott.le_guehennec@etu.uca.fr)
 * @brief Defines functions from namespace masgwickRotations. All functions defined here are documented in madgwickRotations.h
 * @version 0.1
 * @date 2021-12-13
 */
#include "madgwickRotations.h"
#include "Quaternion.h"
#include "Vector.h"

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