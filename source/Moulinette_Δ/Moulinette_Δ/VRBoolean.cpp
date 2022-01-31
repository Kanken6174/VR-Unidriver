#include "VRBoolean.h"

void VRBoolean::setValue(bool value)
{
	VRBoolean::value = value;
}

string VRBoolean::to_string()
{
	string toreturn = "";
	toreturn += (int)VRBoolean::value;
	return toreturn;
}
