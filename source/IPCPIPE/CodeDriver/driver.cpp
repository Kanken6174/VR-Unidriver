#include "IPCServer.h"

using namespace std;

int main() {

	PipeServer* ps = new PipeServer("\\\\.\\pipe\\pipeDriver");

	while (true) {
		cout << "writing to pipe\n";
		while (!ps->WriteToPipe("REQUEST", "\\\\.\\pipe\\pipeMoulinette")) { Sleep(100); }
		cout << "getting answer\n";
		cout << ps->ReadPipe();
		Sleep(100);
	}
}