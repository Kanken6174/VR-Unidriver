#include "VRQuaternion.h"

using namespace moulinette_components;

VRQuaternion::VRQuaternion(int poisition, Quaternion* quaternion): VRComponent(poisition)
{
	this->quaternion = quaternion;
}

VRQuaternion::~VRQuaternion()
{
	quaternion->~Quaternion();
}

std::string VRQuaternion::to_string()
{
	return std::string();
}
