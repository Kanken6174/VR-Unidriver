#include "IPCServer.h"

using namespace std;

int main() {

	PipeServer* ps = new PipeServer("\\\\.\\pipe\\pipeDriver");

	while (true) {
		//cout << "\nwriting to pipe\n";
		while (!ps->WriteToPipe("REQUEST", "\\\\.\\pipe\\pipeMoulinette")) 
		cout << "getting answer\n";
		cout << ps->ReadPipe() << endl;
	}
}