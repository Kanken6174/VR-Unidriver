#include "VRTrigger.h"

VRTrigger::VRTrigger(double val)
{
	setValue(val);
}

VRTrigger::~VRTrigger()
{
}

void VRTrigger::setValue(double val)
{
	this->value = val;
}

double VRTrigger::getValue()
{
	return this->value;
}
