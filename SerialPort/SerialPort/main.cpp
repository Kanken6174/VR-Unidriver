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
	if (w.open("COM2", 74880, 8))
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

int main(int argumentCount, const char* argumentValues[])
{
	//receiveDemo();

	sendDemo();



	getchar();

	return 0;
}