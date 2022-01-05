#include "IPCServer.h"

using namespace std;

int main() {

	PipeServer* ps = new PipeServer("\\\\.\\pipe\\pipeOfDriver");

	while (true) {
		cout << "writing to pipe\n";
		ps->WriteToPipe("REQUEST", "\\\\.\\pipe\\pipeOfMoulinette");
		cout << "getting answer\n";
		cout << ps->ReadPipe();
	}
}