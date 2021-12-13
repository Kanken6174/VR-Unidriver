/**
 * @file Quaternion.cpp
 * @author Elliott Le Guéhennec (elliott.le_guehennec@etu.uca.fr)
 * @brief Defines the methods of struct Quaternion. For doc regarding them see Quaternion.h
 * @version 0.1
 * @date 2021-12-13
 */
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

Quaternion Quaternion::negative() {
	return Quaternion(-x, -y, -z, -w);
}