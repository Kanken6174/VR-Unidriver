#pragma once

#include "framework.h"

struct rots::Quaternion {
private:
	float x;
	float y;
	float z;
	float w;

public:
	Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	Quaternion(rots::Vector* v);
	Quaternion inverse();
};