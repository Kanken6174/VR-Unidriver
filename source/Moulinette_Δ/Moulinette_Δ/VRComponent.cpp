#include "VRComponent.h"
#include "ComponentReflector.h"
#include <iostream>

void VRComponent::settype(int type)
{
	this->sclType = type;
}

int VRComponent::gettype()
{
	return this->sclType;
}

void VRComponent::setFlag(vector<char> flag)
{
	this->flag = flag;
}

vector<char> VRComponent::getFlag() {
	return VRComponent::flag;
}

void VRComponent::receiveData(string data)
{
	ComponentReflector::provideDataToComponent(this, data);
}

string VRComponent::to_string() {
	return ComponentReflector::requestDataFromComponent(this);
}