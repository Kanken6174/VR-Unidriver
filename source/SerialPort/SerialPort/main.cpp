#include <iostream>
#include <fstream>
#include <sstream>
#include "serialPort.h"

using namespace std;

void sendDemo()
{
	SerialPort w; //(const char* portname, int baudrate, char databit);
	if (w.open("COM1", 74880, 8))
	{
		ifstream file("data.txt");
		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				w.send(line.c_str(), line.length());

			}
			file.close();
		}
	}
	else
	{
		cout << "failed...";
	}
}

void receiveDemo()
{
	SerialPort w;
	if (w.open("COM3", 74880, 8))
	{
		char buf[1024];
		while (true)
		{
			memset(buf, 0, 1024);
			w.receive(buf, 1024);
			cout << buf;
		}
	}
}


void Gant() {

	SerialPort w;
	if (w.open("COM3", 74880, 8))
	{
		char buf[1024];
		string ask = "!";
		w.send(ask.c_str(), ask.length());

		while (true)
		{
			memset(buf, 0, 1024);
			w.receive(buf, 1024);
			cout << buf;
		}

	}
}

void requestTram(SerialPort w, float result[]) {

	char buf[1024];

	string ask = "#";							//symbole envoyé a l arduino

	if(!w.send(ask.c_str(), ask.length()))
		throw runtime_error("Erreur send Packet !");


	memset(buf, NULL, 1024);					//mise a NULL tout les éléments du buffeur
	if(!w.receive(buf, 1024))						//reception des données arduino
		throw runtime_error("Erreur receive Packet!");

	if (buf[0] != 'A')
		return;

	string conc;								//string pour la concatenation
	int i = 0;

	buf[0] = NULL;								//on retire le premier element pour eviter les problemes

	for (char s : buf) {
		if (s != NULL) {
			if (s >= '0' && s <= '9' || s == '-') {				// tout chiffre et '-' en evitant toute lettre ou tout élément NULL
				conc += s;													// concatenation
			}
			else {															//arrivée a une nouvelle lettre
				float val=0;
				istringstream iss(conc);									//transformation du string en int 
				iss >> val;

				if(val != 0)
					result[i] = val;

				conc = "";													//remise a 0 de la concatenation
				i = i + 1;
			}
		}
	}
}

SerialPort connect() {
	SerialPort w; //(const char* portname, int baudrate, char databit);
	if (w.open("COM3", 74880, 8))
	{
		return w;
	}
	else {
		throw runtime_error("Port connection erreur !");
	}
}

int main(int argumentCount, const char* argumentValues[])
{
	float response [9];					//a mettre fichier setup
	SerialPort w;

	try
	{
		 w = connect();			//fichier setup port
	}
	catch (const runtime_error& e)
	{
		cout << e.what() << endl;
	}
	

	while (true) {
		requestTram(w, response);
		system("cls");
		for (float s : response) {
			cout << s << endl;
		}
	}



	//giro x y z	
	//accele x y z	
	//magneto x y z
	// 3 vector a faire
	// 
	// try catch


	 char c = getchar();

	return 0;
}