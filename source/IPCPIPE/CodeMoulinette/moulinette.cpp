#include "IPCServer.h"

using namespace std;

int main() {
	string myData = "122|2.889_3.112_0.44456_1.88889|0.1|0.1|0.1|0.1|0.1|0.1|0|0|0|0|";	//une trame de données standard
	string received = "";
	PipeServer* ps = new PipeServer("\\\\.\\pipe\\pipeOfMoulinette");
	
	while (true) {
		received = ps->ReadPipe();
		cout << "Received data\n";
		cout << received;
		
		cout << "got request!!! Sending data right away...\n";
		ps->WriteToPipe(myData, "\\\\.\\pipe\\pipeOfDriver");
	}
}