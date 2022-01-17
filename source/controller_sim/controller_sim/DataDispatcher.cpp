#include"DataDispatcher.h"


	DataDispatcher::DataDispatcher() {
		this->localServer = new PipeServer(this->pipeName);
	}

	DataDispatcher::~DataDispatcher() {
		delete this->localServer;
	}

	void DataDispatcher::feedPipeDataToDrivers(vector<DoMoDriver*> drivers) {
		this->localServer->WriteToPipe("REQUEST", this->targetName);
		string answer = this->localServer->ReadPipe();
		vector<string> splitDriverData = utilities::split(answer, ';');			//à cette étape, on split les trames des différents drivers

		int i = 0;
		for (DoMoDriver* driver : drivers) {
			driver->RunFrameRaw(splitDriverData[i]);
			i++;
			if (i > splitDriverData.size())	//ne devrait arriver que si la trame envoyée contient trop peu de trames
				break;
		}
	}