#pragma once

#include "madgwickRotations.h"

struct madgwickRotations::Quaternion {
public: //constructor
	Quaternion(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}

public: //methods defined in Quaternion.cpp
	Quaternion conjuguate();			//self's conjugate
	double magnitude();					//self's magnitude
	Quaternion reciprocal();			//self's reciprocal
	Quaternion multiplyByReal(double f);//self multiplied by double

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