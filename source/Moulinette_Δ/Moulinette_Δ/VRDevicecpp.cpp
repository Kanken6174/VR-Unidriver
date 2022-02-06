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

	cout << buf << endl;									//recupere la tram

	string conc;								//string pour la concatenation
	bool sw = false;
	string flag(1, buf[0]);
	string quaternion = "";
	int i_quaternion = 0;
	for (char s : buf) {
		if (s >= 'A' && s <= 'Z' || s == NULL) {										// en présence d'une lettre	
		
			if (sw) {
				for (VRComponent* component : this->components) {

					string tmp_flag = component->getFlag();
					vector<string> tmp = utilities::split(tmp_flag, '|');

					for (string elem : tmp) {
						if (elem == flag) {
							if (component->gettype() == -1) {
								quaternion += conc + "|";
								i_quaternion++;

								if(i_quaternion ==3)
									component->receiveData(quaternion);
							}
							else {
								component->receiveData(conc);
							}
							conc = "";
							sw = false;
							break;
						}
					}

				}
				flag = s;
			}
			sw = true;
		}
		else if (s >= '0' && s <= '9' || s == '-') {
			conc += s;
		}

		if (s == NULL)
			break;
	}

}

string VRDevice::to_string()
{
	string toReturn = "";
	
	//toReturn += std::to_string(this->lastLatency)+"|"+this->internalRotation->to_string();	//trame initiale (sans les composants)

	for (VRComponent* component : this->components) {	//ajout des composants
		if (component->gettype() == -1) {
			toReturn += std::to_string(this->lastLatency) + "|" + component->to_string();	//trame initiale (sans les composants)
			break;
		}
	}

	for (VRComponent* component : this->components) {	//ajout des composants
		if(component->gettype() != -1)
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

void VRDevice::setQuaternions(VRQuaternion* component)
{
	this->internalRotation = component;
}

void VRDevice::addComponents(VRComponent* component)
{
	this->components.push_back(component);
}
