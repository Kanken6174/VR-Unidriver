#include "VRDevice.h"

VRDevice::VRDevice(string nom, vector<VRComponent*> components, SerialPort* serialPort) {
	this->serialPort = serialPort;
	this->components = components;
	this->nom = nom;
}

VRDevice::VRDevice()
{
}

void VRDevice::updateValues()
{

}

string VRDevice::to_string()
{
	string toReturn = "";

	//toReturn += std::to_string(this->lastLatency)+"|"+this->internalRotation->to_string();	//trame initiale (sans les composants)

	for (VRComponent* component : this->components) {	//ajout des composants
		toReturn += "|"+component->to_string();
	}

	return toReturn;
}

string VRDevice::getName()
{
	return this->nom;
}

void VRDevice::setName(string name)
{
	this->nom = name;
}

void VRDevice::setSerialport(SerialPort serial)
{
	this->serialPort = &serial;
}

void VRDevice::addComponents(VRComponent* component)
{
	this->components.push_back(component);
}
