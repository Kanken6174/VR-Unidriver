#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>
#include <iostream>
#include <string>

using namespace std;

string GetLastErrorAsString();

class PipeServer {
private:
    HANDLE hPipe = nullptr;
    char buffer[1024];
    std::string pipeName;
    DWORD dwRead = 0;

public:
    PipeServer(string pipeName);
    string ReadPipe();
    bool WriteToPipe(string message, string targetPipe);
    bool isConnected();
};