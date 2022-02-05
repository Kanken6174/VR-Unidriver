#include "VRDevice.h"

VRDevice::VRDevice(string nom, vector<VRComponent*> components, SerialPort serialPort) {
	this->serialPort = serialPort;
	this->components = components;
	this->nom = nom;
}

VRDevice::VRDevice()
{
}

void VRDevice::updateValues()
{
	clock_t t;
	char buf[1024];

	string ask = "#";							//symbole envoyé a l arduino
	t = clock();

	if (!this->serialPort.send(ask.c_str(), ask.length()))
		throw runtime_error("Erreur send Packet !");


	memset(buf, NULL, 1024);					//mise a NULL tout les éléments du buffeur
	if (!this->serialPort.receive(buf, 1024))						//reception des données arduino
		throw runtime_error("Erreur receive Packet!");
	t = clock() - t;
	this->lastLatency = (((float)t) / CLOCKS_PER_SEC);

	if (buf[0] != 'A')
		return;

	cout << buf << endl;

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
	this->serialPort = serial;
}

void VRDevice::addComponents(VRComponent* component)
{
	this->components.push_back(component);
}
