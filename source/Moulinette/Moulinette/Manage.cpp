#include "Manage.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Device.h"



using namespace std;

void Manage::requestTrame(SerialPort w, Device periph)
{
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
		}
		else if (s >= '0' && s <= '9' || s == '-') {
			conc += s;
		}

		if (s == NULL)
			break;
	}
	periph.affichageList();
}
