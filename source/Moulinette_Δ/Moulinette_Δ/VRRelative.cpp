#include "VRRelative.h"
#include <iostream>

void VRRelative::updateMinMax()
{
	if (VRRelative::value > VRRelative::maxValue)
		VRRelative::maxValue = VRRelative::value;
	if (VRRelative::value < VRRelative::minValue)
		VRRelative::minValue = VRRelative::value;
}

void VRRelative::setValue(double value)
{
	VRRelative::value = value;	// = 250
	updateMinMax();	//max 400 min 100 dans cet exemple
	VRRelative::value -= VRRelative::minValue;	// 250-100 = 150
	VRRelative::value /= VRRelative::maxValue;	// 150/400 = 0.375
	VRRelative::value -= 0.5;	//on soustrait 0.5 pour obtenir la valeur relative:  0.375-0.5 = -0.125
	VRRelative::value *= 2; //on multiplie par 2 pour obtenir la véritable valeur (|-1|+1 = 2) : -0.125*2 = -0.25
}

double VRRelative::getValue()
{
	return this->value;
}

void VRRelative::setValueOld(double value)
{
	this->oldValue = value;
}

double VRRelative::getValueOld()
{
	return this->oldValue;
}

VRRelative::VRRelative()
{
	this->settype(RELATIVE);
}

void VRRelative::setMin(double value)
{
	this->minValue = value;
}

void VRRelative::setMax(double value)
{
	this->maxValue = value;
}

void VRRelative::receiveData(string data)
{
	try {
		if (data != "") {
			this->setValueOld(this->getValue());
			this->setValue(std::stod(data));
		}
	}
	catch (std::out_of_range e) {
		//throw away the error if can't convert
	}
}

string VRRelative::to_string()
{
	return std::to_string(VRRelative::value);
}