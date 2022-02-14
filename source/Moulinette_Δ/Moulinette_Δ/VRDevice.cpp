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

	string buf = requestTram();

	string quaternion = std::to_string(this->lastLatency)+"|";
	int i_quaternion = 0;
	
	for (VRComponent* component : this->components) {
		vector<string> tmp = component->getFlag();
		
		for (string elem : tmp) {
			string nul = getDelimitedValueFromRawString(buf, elem);
			if (component->gettype() == -1) {
				quaternion += nul + "|";
				i_quaternion++;
				if (i_quaternion == 9)												// 9 donn�e de quaternions 3*{x,y,z}
					component->receiveData(quaternion);
			}
			else {
				component->receiveData(nul);
			}
			
		}
		
	}
	
}

string VRDevice::requestTram()
{
	clock_t t;
	char buf[1024];

	string ask = "#";							//symbole envoy� a l arduino
	t = clock();

	if (!this->serialPort->send(ask.c_str(), ask.length()))
		throw runtime_error("Erreur send Packet !");

	memset(buf, NULL, 1024);					//mise a NULL tout les �l�ments du buffeur

	if (!this->serialPort->receive(buf, 1024))						//reception des donn�es arduino
		throw runtime_error("Erreur receive Packet!");

	t = clock() - t;
	this->lastLatency = (((float)t) / CLOCKS_PER_SEC);

	if (buf[0] <= 13 ) {		
		HANDLE hCom = *(HANDLE*)this->serialPort->getHandle();

		if (PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR)) {
			cout << "PURGE" << endl;
			try
			{
				cout << this->serialPort->getBaudrate() << endl;
				this->serialPort->connect(this->serialPort);
			}
			catch (const runtime_error& e)
			{
				cout << e.what() << endl;
				getchar();
			}
		}
		else {
			cout << "FAIL" << endl;
		}
		
	}
	//cout << buf << endl;									//recupere la tram

	return buf;
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
		if (component->gettype() != -1)
			toReturn += "|" + component->to_string();
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

void VRDevice::setSerialport(SerialPort* serial)
{
	this->serialPort = serial;
}

void VRDevice::addComponents(VRComponent* component)
{
	this->components.push_back(component);
}
