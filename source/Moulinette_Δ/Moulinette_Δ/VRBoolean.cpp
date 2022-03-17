#include "VRBoolean.h"
#include <iostream>

void VRBoolean::setValue(bool value)
{
	VRBoolean::value = value;
}

bool VRBoolean::getValue()
{
	return this->value;
}

VRBoolean::VRBoolean()
{
	this->settype(0);
}

void VRBoolean::receiveData(const string& data)
{
	try {
		if(data != "")
			this->setValue(std::stod(data));
	}
	catch (std::out_of_range e) {
		//throw away the error if can't convert
	}
}

string VRBoolean::to_string()
{
	return (this->value) ? "1" : "0";
}
