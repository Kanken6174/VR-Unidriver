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
	VRRelative::value = map(value, VRRelative::minValue, VRRelative::maxValue, -1, 1);
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