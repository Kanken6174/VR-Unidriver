#include "IPCServer.h"
#include <random>

using namespace std;

int main() {
	string received = "";
	PipeServer* ps = new PipeServer("\\\\.\\pipe\\pipeMoulinette");
	srand(time(NULL));
	while (true) {
		float rand = ((float)std::rand()) / (float)RAND_MAX;
		float range = 1 - (-1);
		string myData = "20|0_0_0_0|" + std::to_string((rand * range) - 1)+"|-0.3|0.1|0.1|0.1|0.1|0|0|0|0|";	//une trame de données standard
		received = ps->ReadPipe();
		cout << "Received data\n";
		cout << received;
		Sleep(1400);
		cout << "got request!!! Sending data right away...\n";
		ps->WriteToPipe(myData, "\\\\.\\pipe\\pipeDriver");
		Sleep(100);
	}
}