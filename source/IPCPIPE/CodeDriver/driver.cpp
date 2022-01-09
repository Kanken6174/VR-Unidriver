#include "IPCServer.h"

using namespace std;

int main() {

	PipeServer* ps = new PipeServer("\\\\.\\pipe\\pipeD");

	while (true) {
		cout << "writing to pipe\n";
		while (!ps->WriteToPipe("REQUEST", "\\\\.\\pipe\\pipeM")) { Sleep(100); }
		cout << "getting answer\n";
		cout << ps->ReadPipe();
		Sleep(100);
	}
}