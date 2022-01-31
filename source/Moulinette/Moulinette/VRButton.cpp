#include "VRButton.h"

bool VRButton::isPressed() {
	return pressed;
}

std::string VRButton::to_string()
{
	return unsigned int(pressed);
}

VRButton::VRButton(bool press) {
	this->pressed = press;
}


VRButton::~VRButton()
{
}
