#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include "Device.h"
#include "serialPort.h"
#include "IPCServer.h"

using namespace std;
using namespace serialport;

	void requestTramDevice(SerialPort w, Device *periph) {
		clock_t t;

		char buf[1024];

		string ask = "#";							//symbole envoy� a l arduino
		t = clock();
		if (!w.send(ask.c_str(), ask.length()))
			throw runtime_error("Erreur send Packet !");


		memset(buf, NULL, 1024);					//mise a NULL tout les �l�ments du buffeur
		if (!w.receive(buf, 1024))						//reception des donn�es arduino
			throw runtime_error("Erreur receive Packet!");
		t = clock() - t;
		periph->ping = (((float)t) / CLOCKS_PER_SEC);

		if (buf[0] != 'A')
			return;

		cout << buf << endl;

		string conc;								//string pour la concatenation
		list<Device::Prop>::iterator it;
		bool sw = false;
		for (char s : buf) {

			if (s >= 'A' && s <= 'Z' || s == NULL) {										// en pr�sence d'une lettre
				if (sw) {
					float val = 0;
					istringstream iss(conc);									//transformation du string en int 
					iss >> val;
					it->valeur = val;
					sw = false;
					conc = "";
				}
				sw = true;
				it = periph->listProp.begin();
				while (it != periph->listProp.end()) {
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

	char* portName(Device U) {
		char* src = new char[U.port.length() + 1];
		strcpy_s(src, U.port.length() + 1, U.port.c_str());
		return src;
	}

	void GANT() {
		SerialPort w;
		Device gant;
		gant.ReadConfigAndBuildDrivers("gant.dmc");

		try
		{
			w = w.connect(portName(gant), gant.baudrate);
		}
		catch (const runtime_error& e)
		{
			cout << e.what() << endl;
			getchar();
		}

		requestTramDevice(w, &gant);
		//gant.affichageList();
	}

	void SABRE() {
		SerialPort y;
		Device sabre;
		sabre.ReadConfigAndBuildDrivers("sabre.dmc");

		try
		{
			y = y.connect(portName(sabre), sabre.baudrate);
		}
		catch (const runtime_error& e)
		{
			cout << e.what() << endl;
			getchar();
		}

		requestTramDevice(y, &sabre);
	}

	int main(int argumentCount, const char* argumentValues[])
	{
		//thread th1(SABRE);
		//thread th2(GANT);
		//th1.join();
		//th2.join();

		SerialPort w;
		Device gant;
		gant.ReadConfigAndBuildDrivers("gant.dmc");

		try
		{
			w = w.connect(portName(gant), gant.baudrate);
		}
		catch (const runtime_error& e)
		{
			cout << e.what() << endl;
			getchar();
		}

		string piperoot = "\\\\.\\pipe\\";
		string pipenameReceive = piperoot + "pipeMoulinette";
		string pipenameSend = piperoot + "pipeMoulinette";
		PipeServer* psR = new PipeServer(pipenameReceive);
		PipeServer* psS = new PipeServer(pipenameSend);

		while (psR->ReadPipe() != "NULL") {
			requestTramDevice(w, &gant);

			cout << ((psS->WriteToPipe("String donnee pour Driver", pipenameSend)) ? "wrote to pipe\n" : "Error occured\n");

		}
		




		char c = getchar();

		return 0;
	}

