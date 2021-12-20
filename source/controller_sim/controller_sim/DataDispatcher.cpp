#include"DataDispatcher.h"

namespace dispatchers{

	DataDispatcher::DataDispatcher() {

	}

	DataDispatcher::~DataDispatcher() {
		if (this->isPipeConnnected() && this->hPipe != nullptr) {
			DisconnectNamedPipe(this->hPipe);
		}
	}

	bool DataDispatcher::isPipeConnnected() {
		return false;
	}

	string DataDispatcher::readPipe() {
		
		string data = "";
		bool success = ReadFile(this->hPipe, &data, 1024, &(this->dwRead), NULL);
		if (!success) {
			DriverLog("Error, couldn't read pipe, named pipe may be broken");
		}
		return data;
	}

	bool DataDispatcher::connectPipe() {
		wchar_t* wname = (wchar_t*)malloc(sizeof(wchar_t)* this->pipeName.length());
		if (wname == NULL) {
			cerr << "malloc error in dataDispatcher";
			throw new exception("malloc error in dataDispatcher");
			exit(1);
		}
		size_t* pReturnValue = 0;
		wchar_t* wcstr = new wchar_t();
		size_t sizeInWords = 0;
		const char* mbstr = "tests multiples";
		size_t count = 10;
		errno_t errorCode = 0;
		errorCode =	mbstowcs_s(pReturnValue, wcstr, sizeInWords, mbstr, count);
		LPWSTR ptr = wname;
		this->hPipe = CreateFileW(ptr, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		ConnectNamedPipe(this->hPipe, NULL);
		return false;
	}

	bool DataDispatcher::disconnectPipe() {
		return false;
	}

	bool DataDispatcher::feedPipeDataToDrivers() {
		return false;
	}

	vector<string>* DataDispatcher::splitPipeData(string raw) {
		vector<string>* toReturn = new vector<string>();
		if (!isPipeConnnected()) {
			throw exception("broken pipe");
			exit(0);
		}

		string rawData = readPipe();
		
		

		return toReturn;
	}

}