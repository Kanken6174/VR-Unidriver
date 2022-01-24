#include "VRComponent.h"
#include <string>

using namespace moulinette_components;

VRComponent::VRComponent(int position) : position(position) {}

int VRComponent::getPosition() {
	return position;
}