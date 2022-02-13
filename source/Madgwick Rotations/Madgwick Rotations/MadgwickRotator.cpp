/**
 * @file MadgwickRotator.cpp
 * @author Elliot Le Guéhennec (elliott.le_guehennec@etu.uca.fr)
 * @brief Definitions of MadgwickRotator class methods. For documentation see MadgwickRotator.h
 * @version 0.2
 * @date 2022-02-13
 */
#include "MadgwickRotator.h"

void MadgwickRotator::init(Vector zGyro, Vector zAccel, Vector zMagneto) {
	this->zGyro = zGyro;
	this->zAccel = zAccel;
	this->zMagneto = zMagneto;
	inited = true;
	leo = Quaternion(1, 0, 0, 0);
}
void MadgwickRotator::setAStepSize(float value) { aStepSize = value; }

void MadgwickRotator::setMStepSize(float value) { mStepSize = value; }

Quaternion MadgwickRotator::update(time_t delay, Vector gyroscope, Vector accelerometer, Vector magnetometer) {
	Quaternion change, aCorrection, mCorrection;

	//check init
	if (!inited) init(gyroscope, accelerometer, magnetometer);

	//calculate corrections
	aCorrection = correctionFunction(accelerometer, zGyro);
	mCorrection = correctionFunction(magnetometer, zMagneto);

	//calculate change and modify leo
	change = rotate(leo, gyroscope) + aCorrection * aStepSize + mCorrection * mStepSize;
	leo += change * delay / 1000.0;
	return leo;
}

Quaternion MadgwickRotator::changeSincePrevious(Vector g, Quaternion aCorrection, Quaternion mCorrection) {
	return rotate(leo, g) + aCorrection * aStepSize + mCorrection * mStepSize;
}

Quaternion MadgwickRotator::correctionFunction(Vector currentMeasure, Vector reference) {
	//variable declaration
	Quaternion minCon, currentCon, primitive, derivative;

	//calculate primitive correction
	primitive = rotate(leo, currentMeasure) + reference.toQuaternion().negative();

	//calculate those values once because we're using them multiple times
	minCon = leo.reciprocal().conjuguate();
	currentCon = currentMeasure.toQuaternion().conjuguate();

	//derivate correction
	derivative = minCon * currentCon * minCon * primitive * minCon - primitive * minCon * currentCon;

	//calculate gradient
	return derivative / derivative.magnitude();
}