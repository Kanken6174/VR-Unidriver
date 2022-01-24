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
    HANDLE hPipe = INVALID_HANDLE_VALUE;
    HANDLE externPipe = INVALID_HANDLE_VALUE;
    char buffer[1024];
    std::string pipeName;
    DWORD dwRead = 0;
    bool connected = false;
    bool isExternConnected = false;

public:
    PipeServer(string pipeName);
    string ReadPipe();
    bool WriteToPipe(string message, string targetPipe);
    bool isConnected();
};