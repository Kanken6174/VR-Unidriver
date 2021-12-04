#pragma once

#include "rotations.h"

struct rotations::Quaternion {
public: //constructor
	Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

public: //methods defined in Quaternion.cpp
	Quaternion conjuguate();			//self's conjugate
	float magnitude();					//self's magnitude
	Quaternion reciprocal();			//self's reciprocal
	Quaternion multiplyByReal(float f);//self multiplied by float

private: //coordinates of a quaternion
	float x; //real
	float y; //i
	float z; //j
	float w; //k

public: //getters for the coordinates
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	float getW() { return w; }
};