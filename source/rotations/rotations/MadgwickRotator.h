#pragma once
#include <ctime>
#include "Vector.h"
#include "Quaternion.h"
#include "madgwickRotations.h"

using namespace madgwickRotations;

class madgwickRotations::MadgwickRotator
{
private://attributes
	Vector zGyro;
	Vector zAccel;
	Vector zMagneto;
	float aStepSize;
	float mStepSize;
	Quaternion leo;
	bool inited = false;

public://constructor
	MadgwickRotator(float aStepSize = 1, float mStepSize = 1) : aStepSize(aStepSize), mStepSize(mStepSize){}

public://methods defined in MadgwickRotator.cpp
	void init(Vector zGyro, Vector zAccel, Vector zMagneto);
	void setAStepSize(float value);
	void setMStepSize(float value);
	Quaternion update(time_t delay, Vector g, Vector a, Vector m);

private://methods defined in MadgwickRotator.cpp
	Quaternion changeSincePrevious(Vector g, Quaternion aCorrection, Quaternion mCorrection);
	Quaternion correctionFunction(Vector currentMeasure, Vector reference);
};

