#include"DataDispatcher.h"

namespace dispatchers{

	DataDispatcher::DataDispatcher() {

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
		return string("no");
	}

	bool DataDispatcher::connectPipe() {
		wchar_t* wname = (wchar_t*)malloc(sizeof(wchar_t)* this->pipeName.length());
		if (wname == NULL) {
			cerr << "malloc error in dataDispatcher";
			throw new exception("malloc error in dataDispatcher");
			exit(1);
		}
		size_t test1 = 10;
		size_t* pReturnValue;
		wchar_t* wcstr;
		size_t sizeInWords;
		const char* mbstr = "test";
		size_t count;
		errno_t errorCode;
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