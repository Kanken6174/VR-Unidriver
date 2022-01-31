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

string VRAnalog::to_string() {
	string str = "";
	str += VRAnalog::value;
	return str;
}