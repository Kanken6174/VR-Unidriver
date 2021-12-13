#pragma once

#include "madgwickRotations.h"

struct madgwickRotations::Vector {
public: //constructors
	Vector(double x, double y, double z) : x(x), y(y), z(z) {}
	Vector() : x(0), y(0), z(0) {}
	
public: //methods defined in Vector.cpp
	Quaternion toQuaternion(); //converts vector to a quaternion

private: //coordinates of a vector
	double x;
	double y;
	double z;

public: //getters fpr the coordinates
	double getX() { return x; }
	double getY() { return y; }
	double getZ() { return z; }
};