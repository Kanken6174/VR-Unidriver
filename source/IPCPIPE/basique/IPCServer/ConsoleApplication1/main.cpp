// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include "IPCServer.h"

using namespace std;

int main()
{
    string piperoot = "\\\\.\\pipe\\";
    string pipename = piperoot+"testpipe";
    PipeServer* ps = new PipeServer(pipename);


    cout << "made named pipe!\n";
    cout << ((ps->WriteToPipe("hello, i hate microsoft now", pipename)) ? "wrote to pipe\n" : "Error occured\n");
    string str = ps->ReadPipe();
    cout << "Got string: " + str;
}