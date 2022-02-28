#include "VRBoolean.h"

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

void VRBoolean::receiveData(string data)
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
	string toreturn = (this->value) ? "1" : "0";
	return toreturn;
}
