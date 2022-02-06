#include "VRAnalog.h"

void VRAnalog::updateMinMax() {
	if (VRAnalog::value > VRAnalog::maxValue)
		VRAnalog::maxValue = VRAnalog::value;
	if(VRAnalog::value < VRAnalog::minValue)
		VRAnalog::minValue = VRAnalog::value;
}

void VRAnalog::setValue(double value) {
	VRAnalog::value = value;
	updateMinMax();
	VRAnalog::value -= VRAnalog::minValue;
	VRAnalog::value /= VRAnalog::maxValue;
}

double VRAnalog::getValue()
{
	return this->value;
}

void VRAnalog::setValueOld(double value)
{
	this->oldValue = value;
}

double VRAnalog::getValueOld()
{
	return this->oldValue;
}

VRAnalog::VRAnalog()
{
	this->settype(1);
}

void VRAnalog::setMin(double value)
{
	this->minValue = value;
}

void VRAnalog::setMax(double value)
{
	this->maxValue = value;
}

void VRAnalog::receiveData(string data)
{
	try {
		this->setValueOld(this->getValue());
		this->setValue(std::stod(data));
	}
	catch (std::out_of_range e) {
		//throw away the error if can't convert
	}
}



string VRAnalog::to_string() {
	return std::to_string(this->value);
}