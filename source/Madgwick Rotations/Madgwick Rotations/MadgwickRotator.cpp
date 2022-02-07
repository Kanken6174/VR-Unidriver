/**
 * @file MadgwickRotator.cpp
 * @author Elliot Le Guéhennec (elliott.le_guehennec@etu.uca.fr)
 * @brief Definitions of MadgwickRotator class methods. For documentation see MadgwickRotator.h
 * @version 0.1
 * @date 2021-12-13
 */
#include "MadgwickRotator.h"

void MadgwickRotator::init(Vector zGyro, Vector zAccel, Vector zMagneto) {
	this->zGyro = zGyro;
	this->zAccel = zAccel;
	this->zMagneto = zMagneto;
	inited = true;
	leo = Quaternion(0, 0, 0, 0);
}
void MadgwickRotator::setAStepSize(float value) { aStepSize = value; }

void MadgwickRotator::setMStepSize(float value) { mStepSize = value; }

Quaternion MadgwickRotator::update(time_t delay, Vector gyroscope, Vector accelerometer, Vector magnetometer) {
	Quaternion change, aCorrection, mCorrection;

	if (!inited) init(gyroscope, accelerometer, magnetometer);
	aCorrection = correctionFunction(accelerometer, zGyro);
	mCorrection = correctionFunction(magnetometer, zMagneto);
	change = changeSincePrevious(gyroscope, aCorrection, mCorrection);
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