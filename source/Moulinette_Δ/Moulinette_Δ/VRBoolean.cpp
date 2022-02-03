#include "VRBoolean.h"

void VRBoolean::setValue(bool value)
{
	VRBoolean::value = value;
}

void VRBoolean::receiveData(string data)
{
	try {
		this->setValue(std::stod(data));
	}
	catch (std::out_of_range e) {
		//throw away the error if can't convert
	}
}

string VRBoolean::to_string()
{
	string toreturn = "";
	toreturn += (int)VRBoolean::value;
	return toreturn;
}
