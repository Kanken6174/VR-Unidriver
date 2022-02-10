#include "IPCServer.h"

using namespace std;

int main() {
	string myData = "20|0_0_0_0|0.1|0.1|0.1|0.1|0.1|0.1|0|0|0|0|";	//une trame de données standard
	string received = "";
	PipeServer* ps = new PipeServer("\\\\.\\pipe\\pipeMoulinette");
	
	while (true) {
		received = ps->ReadPipe();
		cout << "Received data\n";
		cout << received;
		Sleep(1400);
		cout << "got request!!! Sending data right away...\n";
		ps->WriteToPipe(myData, "\\\\.\\pipe\\pipeDriver");
		Sleep(100);
	}
}