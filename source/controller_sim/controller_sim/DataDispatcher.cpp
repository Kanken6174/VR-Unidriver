#include"DataDispatcher.h"


	DataDispatcher::DataDispatcher() {
		this->localServer = new PipeServer(this->pipeName);
	}

	DataDispatcher::~DataDispatcher() {
		delete this->localServer;
	}

	void DataDispatcher::feedPipeDataToDrivers(vector<DoMoDriver*> drivers) {
		this->localServer->WriteToPipe("REQUEST", this->targetName);
		string answer = this->localServer->ReadPipe();							//bloquant
		vector<string> splitDriverData = utilities::split(answer, ';', true);	//� cette �tape, on split les trames des diff�rents drivers, on enl�ve le s�parateur

		int index = 0;
		for (DoMoDriver* driver : drivers) {
			driver->RunFrameRaw(splitDriverData[index]);	// ce sera une trame standard de type d�lai|quaternion|composant1|composant2|...
			index++;
			if (index > splitDriverData.size())	//ne devrait arriver que si la trame envoy�e contient trop peu de trames
				break;
		}
	}