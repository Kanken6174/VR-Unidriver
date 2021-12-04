#pragma once

#include "rotations.h";

struct rotations::Vector {
public: //constructor
	Vector(float x, float y, float z) : x(x), y(y), z(z) {}
	
public: //methods defined in Vector.cpp
	Quaternion toQuaternion(); //converts vector to a quaternion

private: //coordinates of a vector
	float x;
	float y;
	float z;

public: //getters fpr the coordinates
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
};