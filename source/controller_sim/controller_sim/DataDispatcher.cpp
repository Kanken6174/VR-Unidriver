#include"DataDispatcher.h"


	DataDispatcher::DataDispatcher() {
		this->pipeName = "\\\\.\\pipe\\pipeDriver";
		this->localServer = new PipeServer("\\\\.\\pipe\\pipeDriver");
	}

	DataDispatcher::~DataDispatcher() {
		delete this->localServer;
	}

	void DataDispatcher::feedPipeDataToDrivers(vector<DoMoDriver*>* drivers) {
		if (this->localServer == NULL) {
			DriverLog("Error, localserver was null");
			return;
		}

		if (cyclesToIgnore > 0)
		{
			cyclesToIgnore--;
			return;
		}
		clock_t t;
		t = clock();
		this->doPipeAction();
		t = clock() - t;
		//DriverLog("pipe time : % d ms", t);
		long latency = t;
		if (this->lastFrame == "")
			return;

		vector<string> splitDriverData = utilities::split(this->lastFrame, ';', true);	//� cette �tape, on split les trames des diff�rents drivers, on enl�ve le s�parateur

		int index = 0;
		for (DoMoDriver* driver : *drivers) {
			driver->setLastLatency(latency);	//latence du hardware
			driver->RunFrameRaw(splitDriverData[index]);	// ce sera une trame standard de type d�lai|quaternion|composant1|composant2|...
			index++;
			if (index > splitDriverData.size())	//ne devrait arriver que si la trame envoy�e contient trop peu de trames
				break;
		}

	}

	void DataDispatcher::doPipeAction()
	{
			bool succeeded = this->localServer->WriteToPipe("REQUEST", this->targetName);
			if (!succeeded) {
				DriverLog("Write failed");
				return;
			}
			string answer = this->localServer->ReadPipe();//bloquant
			DriverLog(answer.c_str());
			if (answer == "" || answer.size() < 4) {
				DriverLog("read failed");
				return;
			}
			else {
				this->lastFrame = answer;
			}
	}
