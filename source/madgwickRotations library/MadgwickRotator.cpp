#include "pch.h"
#include "MadgwickRotator.h"

void MadgwickRotator::init(Vector zGyro, Vector zAccel, Vector zMagneto) {
	this->zGyro = zGyro;
	this->zAccel = zAccel;
	this->zMagneto = zMagneto;
	inited = true;
}
void MadgwickRotator::setAStepSize(float value) { aStepSize = value; }

void MadgwickRotator::setMStepSize(float value) { mStepSize = value; }

Quaternion MadgwickRotator::update(time_t delay, Vector g, Vector a, Vector m) {
	Quaternion change, aCorrection, mCorrection;

	if (!inited) init(g, a, m);
	aCorrection = correctionFunction(a, zGyro);
	mCorrection = correctionFunction(m, zMagneto);
	change = changeSincePrevious(g, aCorrection, mCorrection);
	leo = addQuaternions(leo, change.multiplyByReal(delay / 1000.0));
	return leo;
}

Quaternion MadgwickRotator::changeSincePrevious(Vector g, Quaternion aCorrection, Quaternion mCorrection) {
	Quaternion tmp = rotate(leo, g);
	tmp = addQuaternions(tmp, aCorrection.multiplyByReal(aStepSize));
	return addQuaternions(tmp, mCorrection.multiplyByReal(mStepSize));
}

Quaternion MadgwickRotator::correctionFunction(Vector currentMeasure, Vector reference) {
	//variable declaration
	Quaternion tmpA, tmpB;
	Quaternion minCon, currentCon, primitive;

	//calculate primitive correction
	tmpA = rotate(leo, currentMeasure);
	tmpB = reference.toQuaternion().negative();
	primitive = addQuaternions(tmpA, tmpB);

	//calculate those values once because we're using them multiple times
	minCon = leo.reciprocal().conjuguate();
	currentCon = currentMeasure.toQuaternion().conjuguate();

	//derivate primitive
	tmpA = multiplyQuaternions(minCon, currentCon);
	tmpA = multiplyQuaternions(tmpA, minCon);
	tmpA = multiplyQuaternions(tmpA, primitive);
	tmpA = multiplyQuaternions(tmpA, minCon);

	tmpB = multiplyQuaternions(primitive, minCon);
	tmpB = multiplyQuaternions(tmpB, currentCon);

	tmpA = addQuaternions(tmpA, tmpB.negative());

	//divide by magnitude and return
	return tmpA.multiplyByReal(1.0 / tmpA.magnitude());
}