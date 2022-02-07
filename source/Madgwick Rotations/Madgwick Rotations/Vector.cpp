/**
 * @file Vector.cpp
 * @author Elliott Le Guéhennec (elliott.le_guehennec@etu.uca.fr)
 * @brief Defines methods for struct Vector. For doc see Vector.h
 * @version 0.1
 * @date 2021-12-13
 */
#pragma once

#include "Vector.h"
#include "Quaternion.h"

using namespace madgwickRotations;

madgwickRotations::Vector::Vector(double x, double y, double z)
	: x(x), y(y), z(z) {}

madgwickRotations::Vector::Vector(){}

Quaternion Vector::toQuaternion() {
	return Quaternion(x, y, z, 0);
}

double Vector::getX() { return x; }
double Vector::getY() { return y; }
double Vector::getZ() { return z; }