#include "VRComponent.h"
#include <iostream>

void VRComponent::settype(int type)
{
	this->sclType = type;
}

int VRComponent::gettype()
{
	return this->sclType;
}

void VRComponent::setFlag(vector<string> flag)
{
	this->flag = flag;
}

vector<string> VRComponent::getFlag() {
	return VRComponent::flag;
}

void VRComponent::receiveData(const string& data)
{
	this->receiveData(data);
}

string VRComponent::to_string()
{
	return this->to_string();
}


