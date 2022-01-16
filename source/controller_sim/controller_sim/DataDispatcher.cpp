#include"DataDispatcher.h"

namespace dispatchers{

	DataDispatcher::DataDispatcher() {
		this->localServer = new PipeServer(this->pipeName);
	}

	DataDispatcher::~DataDispatcher() {
		delete this->localServer;
	}

	bool DataDispatcher::feedPipeDataToDrivers(vector<DoMoDriver*> drivers) {
		this->localServer->WriteToPipe("REQUEST", this->targetName);
		string anwser = this->localServer->ReadPipe();

		for (DoMoDriver* driver : drivers) {
			driver->RunFrameStub();
		}

		return false;
	}

}