#include "VRComponent.h"

void VRComponent::settype(int type)
{
	this->sclType = type;
}

int VRComponent::gettype()
{
	return this->sclType;
}

void VRComponent::setPosition(int position)
{
	this->position = position;
}

int VRComponent::getPosition() {
	return VRComponent::position;
}

void VRComponent::receiveData(string data)
{
	throw new exception("Abstract method was called");
}

string VRComponent::to_string() {
	string str = "";
	str += VRComponent::position;
	return str;
}