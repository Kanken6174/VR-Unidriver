#include <stdio.h>
#include <string.h>
#include <iostream>
#include <WinSock2.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>

namespace serialport
{
class SerialPort
{
public:
	SerialPort();
	~SerialPort();

	bool open(const char* portname, int baudrate, char databit);
	void close();

	int send(const void* buf, int len);
	int receive(void* buf, int maxlen);

	SerialPort connect();

	void setPort(char* port);
	void setBaudrate(int baud);

private:
	int pHandle[16];
	char* port;
	int baudrate;
};

}