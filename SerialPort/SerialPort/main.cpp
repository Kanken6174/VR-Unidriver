#include <iostream>
#include "serialPort.h"

using namespace std;

void sendDemo()
{
	SerialPort w;
	if (w.open("COM1", 74880, 0, 8, 1))
	{
		for (int i = 0; i < 10; i++)
		{
			w.send("send...", 7);
		}
		cout << "send demo finished...";
	}
	else
	{
		cout << "failed...";
	}
}

void receiveDemo()
{
	SerialPort w;
	if (w.open("COM2", 74880, 0, 8, 1))
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

	sendDemo();

	//receiveDemo();

	getchar();

	return 0;
}