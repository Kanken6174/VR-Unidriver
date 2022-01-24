
class SerialPort
{
public:
	SerialPort();
	~SerialPort();


	bool open(const char* portname, int baudrate, char databit);


	void close();


	int send(const void* buf, int len);


	int receive(void* buf, int maxlen);

private:
	int pHandle[16];
};

