#include "IPCServer.h"

using namespace std;

int main() {

	PipeServer* ps = new PipeServer("\\\\.\\pipe\\pipeDriver");

	while (true) {
		cout << "writing to pipe\n";

		while (!ps->WriteToPipe("REQUEST", "\\\\.\\pipe\\pipeMoulinette")) { 
			Sleep(1000); 
		}

		cout << "getting answer\n";
		cout << ps->ReadPipe() << endl;
		cout << "Finish read" << endl;
		Sleep(100);
	}
}