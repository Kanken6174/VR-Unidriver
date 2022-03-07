﻿#include <stdio.h>
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

	bool isConnected();
	void connect(SerialPort* w);

	void setPort(char* port);
	void setBaudrate(int baud);

	int getBaudrate();
	int* getHandle();

private:
	int pHandle[16];
	char* port;
	int baudrate;
	bool connected;
};

}