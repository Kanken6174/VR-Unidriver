#include "IPCServer.h"

PipeServer::PipeServer(std::string pipeName) {
    this->pipeName = pipeName;
    LPCSTR ptr = pipeName.c_str();

    this->hPipe = CreateNamedPipeA(ptr, PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, 1, 1024 * 16, 1024 * 16, NMPWAIT_USE_DEFAULT_WAIT, NULL);

    if (!isConnected()) {
        cout << "pipe failed to connect!!!\n";
        cout << GetLastErrorAsString();
    }
}

std::string PipeServer::ReadPipe() {
    std::string toReturn = "";
    if (!ConnectNamedPipe(this->hPipe, NULL)) {
        LPDWORD dwordPtr = &this->dwRead;    //juste un pointeur vers un DWORD
        cout << GetLastErrorAsString();

        while (ReadFile(this->hPipe, buffer, sizeof(buffer) - 1, dwordPtr, NULL)) { //on lit jusqu'� 1023 caract�res � la fois, autant de fois que n�cessaire
            this->buffer[dwRead] = '\0';
            toReturn += this->buffer;
        }

        memset(this->buffer, 0, sizeof(this->buffer));  //un peu overkill mais on efface le buffer compl�tement et de force (on le remplit de 0)
    }
    DisconnectNamedPipe(this->hPipe);

    return toReturn;
}

bool PipeServer::WriteToPipe(std::string message, string targetPipe = "") {
    if (targetPipe == "")
        targetPipe = this->pipeName;

    LPCSTR lpcStr = targetPipe.c_str();
    HANDLE handlePipe = INVALID_HANDLE_VALUE;
    DWORD dwordsEcrits = 0;

    handlePipe = CreateFileA(lpcStr,GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

    if (handlePipe != INVALID_HANDLE_VALUE)
    {
        LPDWORD dwordPtr = &dwordsEcrits;

        if (!WriteFile(handlePipe, message.c_str(), message.length() + 1, dwordPtr, NULL)) {
            return false;
        }

        CloseHandle(handlePipe);
    }
    else {
        cout << "Error, pipe handle was invalid, couldn't open pipe "+ targetPipe + "\n";
        cout << GetLastErrorAsString();
        return false;
    }
    return true;
}

bool PipeServer::isConnected() {
    return (this->hPipe != INVALID_HANDLE_VALUE);
}