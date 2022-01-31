#include "VRDevice.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>




VRDevice::VRDevice(list<VRComponent> , SerialPort serial)
{
	this->serialPort = serial;
	this->components = Vrcomponents;
}

void VRDevice::updateValues(){
    requestTramDevice(this->lastLatence,this->components, this->serialPort);
}


string VRDevice::to_string(){
    list<VRComponent>::iterator it;
    string message;
    it=components.begin();
    while(it != components.end()){
		message += components.value+"|";
    }
    return message;
}


void requestTramDevice(float lastLatence, list<VRComponent> components, SerialPort w) {
	clock_t t;

	char buf[1024];

	string ask = "#";							//symbole envoy? a l arduino
	t = clock();
	if (!w.send(ask.c_str(), ask.length()))
		throw runtime_error("Erreur send Packet !");


	memset(buf, NULL, 1024);					//mise a NULL tout les ?l?ments du buffeur
	if (!w.receive(buf, 1024))						//reception des donn?es arduino
		throw runtime_error("Erreur receive Packet!");
	t = clock() - t;
	lastLatence = (((float)t) / CLOCKS_PER_SEC);

	if (buf[0] != 'A')
		return;

	//cout << buf << endl;

	string conc;								//string pour la concatenation
	list<VRDevice::Prop>::iterator it;
	bool sw = false;
	for (char s : buf) {

		if (s >= 'A' && s <= 'Z' || s == NULL) {										// en pr?sence d'une lettre
			if (sw) {
				float val = 0;
				istringstream iss(conc);									//transformation du string en int 
				iss >> val;
				it->valeur = val;
				sw = false;
				conc = "";
			}
			sw = true;
			it = components.begin();
			while (it != components.end()) {
				string tmp_string(1, s);
				if (it->flag == tmp_string) {
					break;
				}
				it++;
			}
		}
		else if (s >= '0' && s <= '9' || s == '-') {
			conc += s;
		}

		if (s == NULL)
			break;
	}
}