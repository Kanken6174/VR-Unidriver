#include <iostream>
#include <fstream>
#include <sstream>
#include "Device.h"
#include "serialPort.h"

using namespace std;


SerialPort connect(char* p, int b) {
	SerialPort w; //(const char* portname, int baudrate, char databit);
	if (w.open(p, b, 8))
	{
		return w;
	}
	else {
		throw runtime_error("Port connection erreur !");
	}
}


void requestTramDevice(SerialPort w, Device periph) {
	char buf[1024];

	string ask = "#";							//symbole envoyé a l arduino

	if (!w.send(ask.c_str(), ask.length()))
		throw runtime_error("Erreur send Packet !");


	memset(buf, NULL, 1024);					//mise a NULL tout les éléments du buffeur
	if (!w.receive(buf, 1024))						//reception des données arduino
		throw runtime_error("Erreur receive Packet!");

	if (buf[0] != 'A')
		return;

	cout << buf << endl;

	string conc;								//string pour la concatenation
	list<Device::Prop>::iterator it;
	bool sw = false;
	for (char s : buf) {

			if (s >= 'A' && s <= 'Z' || s == NULL) {										// en présence d'une lettre
				if (sw) {
					float val = 0;
					istringstream iss(conc);									//transformation du string en int 
					iss >> val;
					it->valeur = val;
					sw = false;
					conc = "";
				}
				sw = true;
				it = periph.listProp.begin();
				while (it != periph.listProp.end()) {
					string tmp_string(1, s);
					if (it->flag == tmp_string) {
						break;
					}
					it++;
				}
			} else if(s >= '0' && s <= '9' || s == '-') {
				conc += s;
			}
		
			if (s == NULL)
				break;
		}
}

int main(int argumentCount, const char* argumentValues[])
{
	float response [9];					//a mettre fichier setup
	SerialPort w;

	Device gant;
	gant.ReadConfigAndBuildDrivers();

	try
	{
		// a mettre dans une fonction
		char* src = new char[gant.port.length() + 1];
		strcpy_s(src, gant.port.length() + 1,gant.port.c_str());

		w = connect(src,gant.baudrate);			
	}
	catch (const runtime_error& e)
	{
		cout << e.what() << endl;
		getchar();
	}
	

	requestTramDevice(w, gant);

	/*
	for (int i = 0; i < 100; i++) {
		requestTramDevice(w, gant);
	}
	*/
	 char c = getchar();

	return 0;
}