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
		if (!this->connected) {
			if (!logged) {
				logged = true;
				DriverLog(("still not connected after connect call, retrying...\n" + GetLastErrorAsString() + std::to_string((DWORD)this->hPipe) + "\n").c_str());
			}
			Sleep(10);
		}
	} while (this->connected == false);
	DriverLog(("Connected a client to the local pipe " + std::to_string((DWORD)this->hPipe)).c_str());
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
		if (!success)
			DriverLog("Failed to disconnect from pipe");
		else
			DriverLog("Successfully disconnected pipe");
	}
	return toReturn;
}

bool PipeServer::WriteToPipe(std::string message, string targetPipe = "") {
	message[message.length()] = '\0';
	if (targetPipe == "")
		targetPipe = this->pipeName;

	LPCSTR lpcStr = targetPipe.c_str();
	DWORD dwordsEcrits = 0;

	if (this->connected == true) {
		this->connected = false;
	}

	BOOL returned = WaitNamedPipeA(lpcStr, 2000);
	if (returned == 0) {
		return false;
	}
	this->hPipe = CreateFileA(lpcStr, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	this->connected = (this->hPipe != INVALID_HANDLE_VALUE);

	if (this->connected)
	{
		LPDWORD dwordPtr = &dwordsEcrits;

		if (!WriteFile(this->hPipe, message.c_str(), message.length() + 1, dwordPtr, NULL)) {
			DriverLog("Couldn't write to file");
			return false;
		}
		bool returned = CloseHandle(this->hPipe);
		if (returned)
			if (this->hPipe != INVALID_HANDLE_VALUE)
				this->connected = INVALID_HANDLE_VALUE;
	}
	else {
		DriverLog(("Error, pipe handle was invalid, couldn't open pipe " + targetPipe + "\n").c_str());
		DriverLog(GetLastErrorAsString().c_str());
		return false;
	}
	return true;
}

bool PipeServer::isConnected() {
	return (this->hPipe != INVALID_HANDLE_VALUE);
}
