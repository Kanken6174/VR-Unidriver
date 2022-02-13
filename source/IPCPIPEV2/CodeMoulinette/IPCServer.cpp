#include "IPCServer.h"

PipeServer::PipeServer(std::string pipeName) {
	this->pipeName = pipeName;
	LPCSTR ptr = pipeName.c_str();

	this->hPipe = CreateNamedPipeA(ptr, PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, 1, 1024 * 16, 1024 * 16, NMPWAIT_WAIT_FOREVER, NULL);
	if (!isConnected()) {
		cout << "pipe failed to connect!!!\n";
		cout << GetLastErrorAsString();
	}
	else {
		cout << "successfully created pipe " + pipeName + " with handle " + std::to_string((DWORD)this->hPipe) + " invalid is " + std::to_string((DWORD)INVALID_HANDLE_VALUE) + "\n";
	}
}

std::string PipeServer::ReadPipe() {
	std::string toReturn = "";
	char buf[1024];
	//cout << "attempting to connect a client to the local pipe with handle " + std::to_string((DWORD)this->hPipe) + "\n";
	do {
		this->connected = ConnectNamedPipe(this->hPipe, NULL);
		Sleep(2);
	} while (this->connected == false);
	if (this->connected) {
		LPDWORD dwordPtr = &this->dwRead;    //juste un pointeur vers un DWORD

		while (ReadFile(this->hPipe, buf, sizeof(buf) - 1, dwordPtr, NULL)) { //on lit jusqu'à 1023 caractères à la fois, autant de fois que nécessaire
			buf[dwRead] = '\0';
			toReturn += buf;
		}

		memset(buf, 0, sizeof(buf));  //un peu overkill mais on efface le buffer complètement et de force (on le remplit de 0)
	}
	else {
		//cout << "still not connected...\n";
	}
	if (this->connected) {
		//cout << "was connected, disconnecting...\n";
		DisconnectNamedPipe(this->hPipe);
		//cout << success ? "Successfully disconnected" : "Error disconnecting" + GetLastErrorAsString();
	}


	return toReturn;
}

bool PipeServer::WriteToPipe(std::string message, string targetPipe = "") {
	message[message.length()] = '\0';
	if (targetPipe == "")
		targetPipe = this->pipeName;

	LPCSTR lpcStr = targetPipe.c_str();
	DWORD dwordsEcrits = 0;

	if (this->isExternConnected == true) {
		//cout << "already connected to external pipe\n";
		this->isExternConnected = false;
	}

	BOOL returned = WaitNamedPipeA(lpcStr, 1000);
	if (returned == 0) {
		//cout << "pipe " + targetPipe + " timed out, resume wait...\n";
		return false;
	}
	this->externPipe = CreateFileA(lpcStr, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	this->isExternConnected = (this->externPipe != INVALID_HANDLE_VALUE);
	//cout << (this->isExternConnected) ? "Connected to distant pipe\n" : "not connected to distant pipe!\n";

	if (this->isExternConnected)
	{
		LPDWORD dwordPtr = &dwordsEcrits;

		if (!WriteFile(this->externPipe, message.c_str(), message.length() + 1, dwordPtr, NULL)) {
			return false;
		}
		bool returned = CloseHandle(this->externPipe);
		//if (!returned)
			//cout << "error closing pipe!";
		//else
			if (this->externPipe != INVALID_HANDLE_VALUE)
				this->externPipe = INVALID_HANDLE_VALUE;
	}
	else {
		//cout << "Error, pipe handle was invalid, couldn't open pipe " + targetPipe + "\n";
		//cout << GetLastErrorAsString();
		return false;
	}
	return true;
}

bool PipeServer::isConnected() {
	return (this->hPipe != INVALID_HANDLE_VALUE);
}