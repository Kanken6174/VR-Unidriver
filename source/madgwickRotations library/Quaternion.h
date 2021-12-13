#pragma once

#include "madgwickRotations.h"

struct madgwickRotations::Quaternion {
public: //constructors
	Quaternion(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}
	Quaternion() : x(0), y(0), z(0), w(0) {}

public: //methods defined in Quaternion.cpp
	Quaternion conjuguate();			//self's conjugate
	double magnitude();					//self's magnitude
	Quaternion reciprocal();			//self's reciprocal
	Quaternion multiplyByReal(double value);//self multiplied by double
	Quaternion negative();				// - self

private: //coordinates of a quaternion
	double x; //real
	double y; //i
	double z; //j
	double w; //k

public: //getters for the coordinates
	double getX() { return x; }
	double getY() { return y; }
	double getZ() { return z; }
	double getW() { return w; }
};