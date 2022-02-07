#include"DataDispatcher.h"


	DataDispatcher::DataDispatcher() {
		this->pipeName = "\\\\.\\pipe\\pipeDriver";
		this->localServer = new PipeServer("\\\\.\\pipe\\pipeDriver");
		//std::thread Thread = std::thread([this] { this->beginThreadedPipeDataUpdater(std::ref(lastFrame)); });
	}

	DataDispatcher::~DataDispatcher() {
		delete this->localServer;
	}

	void DataDispatcher::feedPipeDataToDrivers(vector<DoMoDriver*> drivers) {
		if (this->localServer == NULL) {
			DriverLog("Error, localserver was null");
			return;
		}

		if (cyclesToIgnore > 0)
		{
			cyclesToIgnore--;
			return;
		}

		this->doPipeAction();

		if (this->lastFrame == "")
			return;

		vector<string> splitDriverData = utilities::split(this->lastFrame, ';', true);	//� cette �tape, on split les trames des diff�rents drivers, on enl�ve le s�parateur
		DriverLog("SplitData");
		int index = 0;
		for (DoMoDriver* driver : drivers) {
			driver->RunFrameRaw(splitDriverData[index]);	// ce sera une trame standard de type d�lai|quaternion|composant1|composant2|...
			index++;
			if (index > splitDriverData.size())	//ne devrait arriver que si la trame envoy�e contient trop peu de trames
				break;
		}
		DriverLog("Done dispatching");
	}

	void DataDispatcher::doPipeAction()
	{
			bool succeeded = this->localServer->WriteToPipe("REQUEST", this->targetName);
			if (!succeeded) {
				DriverLog("Write failed");
				return;
			}
			DriverLog("Done Writing");
			string answer = this->localServer->ReadPipe();//bloquant
			DriverLog(answer.c_str());
			if (answer == "" || answer.size() < 4) {
				DriverLog("read failed");
				return;
			}
			DriverLog("Done Reading");
	}
