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

	SerialPort connect(char* p, int b);

private:
	int pHandle[16];
};

}