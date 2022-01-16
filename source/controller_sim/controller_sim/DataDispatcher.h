#pragma once

#ifndef DISPATCHER
#define DISPATCHER


#include "controller_sim.h"
#include "IPCIPE/IPCServer.h"

using namespace std;
using namespace vr;

namespace dispatchers {
	class DataDispatcher
	{
	private:
		vector<string> splitData;
		string pipeName = "\\\\.\\pipe\\DriverPipe";
		string targetName = "\\\\.\\pipe\\MoulinettePipe";
		PipeServer* localServer;

	public:
		DataDispatcher();
		~DataDispatcher();

		virtual bool feedPipeDataToDrivers(vector<DoMoDriver*> drivers);
	};
}

#endif