#include "VRComponent.h"

void VRComponent::settype(int type)
{
}

int VRComponent::gettype()
{
	return 0;
}

int VRComponent::getPosition() {
	return VRComponent::position;
}

string VRComponent::to_string() {
	string str = "";
	str += VRComponent::position;
	return str;
}