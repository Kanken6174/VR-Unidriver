#include "VRComponent.h"
int VRComponent::getPosition() {
	return VRComponent::position;
}

string VRComponent::to_string() {
	string str = "";
	str += VRComponent::position;
	return str;
}