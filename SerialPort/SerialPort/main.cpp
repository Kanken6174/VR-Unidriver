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
	w.send(ask.c_str(), ask.length());


	memset(buf, NULL, 1024);					//mise a NULL tout les éléments du buffeur
	w.receive(buf, 1024);						//reception des données arduino

	cout << buf << endl;

	string conc;								//string pour la concatenation
	//float result[10];								// tableau a renvoyer (11) pour la trame 
	int i = 0;
	buf[0] = NULL;								//on retire le premier element pour eviter les problemes

	for (char s : buf) {
		if (s != NULL) {
			if (s >= '0' && s <= '9' || s == '-') {				// tout chiffre et '-' en evitant toute lettre ou tout élément NULL
				conc += s;													// concatenation
			}
			else {															//arrivée a une nouvelle lettre

				int val;
				istringstream iss(conc);									//transformation du string en int 
				iss >> val;

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
		cout << "Not Connected";
	}
}

int main(int argumentCount, const char* argumentValues[])
{
	float response [10];
	SerialPort w = connect();
	
	requestTram(w, response);

	for (float s : response) {
		cout << s << endl;
	}



	getchar();

	return 0;
}