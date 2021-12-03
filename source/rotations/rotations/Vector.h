#pragma once

#include "framework.h";

struct rots::Vector {
private:
	float x;
	float y;
	float z;

public:
	Vector(float x, float y, float z) : x(x), y(y), z(z) {}
	Quaternion toQuaternion();
};