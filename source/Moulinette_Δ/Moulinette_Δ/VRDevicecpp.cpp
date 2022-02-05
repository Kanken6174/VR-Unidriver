#include "VRDevice.h"

VRDevice::VRDevice(string nom, vector<VRComponent*> components, SerialPort* serialPort) {
	this->serialPort = serialPort;
	this->components = components;
	this->nom = nom;
}

void VRDevice::updateValues()
{

}

string VRDevice::to_string()
{
	string toReturn = "";

	toReturn += std::to_string(this->lastLatency)+"|"+this->internalRotation->to_string();	//trame initiale (sans les composants)

	for (VRComponent* component : this->components) {	//ajout des composants
		toReturn += "|"+component->to_string();
	}

	return toReturn;
}