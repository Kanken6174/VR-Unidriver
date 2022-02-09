#include "IPCServer.h"
#include "../driverlog.h"

PipeServer::PipeServer(std::string pipeName) {
	this->pipeName = pipeName;
	LPCSTR ptr = pipeName.c_str();

	this->hPipe = CreateNamedPipeA(ptr, PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, 1, 1024 * 16, 1024 * 16, NMPWAIT_WAIT_FOREVER, NULL);
	if (!isConnected()) {
		DriverLog("pipe failed to connect!!!\n");
		DriverLog(GetLastErrorAsString().c_str());
	}
	else {
		DriverLog(("successfully created pipe " + pipeName + " with handle " + std::to_string((DWORD)this->hPipe) + " invalid is " + std::to_string((DWORD)INVALID_HANDLE_VALUE) + "\n").c_str());
	}
}

std::string PipeServer::ReadPipe() {
	std::string toReturn = "";
	char buf[1024];
	bool logged = false;
	do {
		this->connected = ConnectNamedPipe(this->hPipe, NULL);
	} while (this->connected == false);
	if (this->connected) {
		LPDWORD dwordPtr = &this->dwRead;    //juste un pointeur vers un DWORD

		while (ReadFile(this->hPipe, buf, sizeof(buf) - 1, dwordPtr, NULL)) { //on lit jusqu' 1023 caractres  la fois, autant de fois que ncessaire
			buf[dwRead] = '\0';
			toReturn += buf;
		}

		memset(buf, 0, sizeof(buf));  //un peu overkill mais on efface le buffer compltement et de force (on le remplit de 0)
	}
	if (this->connected) {
		bool success = DisconnectNamedPipe(this->hPipe);
	}
	return toReturn;
}

bool PipeServer::WriteToPipe(std::string message, string targetPipe = "") {
	message[message.length()] = '\0';
	if (targetPipe == "") {
		cout << "target was null, set to self\n";
		targetPipe = this->pipeName;
	}

	LPCSTR lpcStr = targetPipe.c_str();
	DWORD dwordsEcrits = 0;

	if (this->isExternConnected == true) {
		this->isExternConnected = false;
	}
	cout << "Waiting for named pipe...\n";
	BOOL returned = WaitNamedPipeA(lpcStr, 1000);
	if (returned == 0) {
		cout << "waiting for a pipe on " + targetPipe + " timed out\n";
		return false;
	}
	cout << "Done\n";
	this->externPipe = CreateFileA(lpcStr, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	this->isExternConnected = (this->externPipe != INVALID_HANDLE_VALUE);

	if (this->isExternConnected)
	{
		LPDWORD dwordPtr = &dwordsEcrits;

		if (!WriteFile(this->externPipe, message.c_str(), message.length() + 1, dwordPtr, NULL)) {
			cout << "failed to write to " + std::to_string((DWORD)this->externPipe) + "\n";
			return false;
		}
		bool returned = CloseHandle(this->externPipe);
		if (returned) {
			if (this->externPipe != INVALID_HANDLE_VALUE)
				this->externPipe = INVALID_HANDLE_VALUE;
		}
		else {
			cout << "failed to close handle\n";
		}

	}
	else {
		CloseHandle(this->externPipe);
		cout << "was not connected, write attempt failed\n";
		return false;
	}
	return true;
}

bool PipeServer::isConnected() {
	return (this->hPipe != INVALID_HANDLE_VALUE);
}
