#include "VRComponent.h"
#include "ComponentReflector.h"

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
	ComponentReflector::provideDataToComponent(this, data);
}

string VRComponent::to_string() {
	return ComponentReflector::requestDataFromComponent(this);
}