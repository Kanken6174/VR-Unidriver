#pragma once

#ifndef DISPATCHER
#define DISPATCHER


#include "controller_sim.h"

using namespace std;
using namespace vr;

namespace dispatchers {
	class DataDispatcher
	{
	private:
		vector<string> splitData;
		vector<string>* splitPipeData(string RawPipeData);
		string pipeName = "\\\\.\\domocap\\DriverPipe";

		HANDLE hPipe = nullptr;
		DWORD dwRead = 0;

	public:
		DataDispatcher();
		~DataDispatcher();

		virtual bool isPipeConnnected();
		virtual bool connectPipe();
		virtual bool disconnectPipe();
		virtual string readPipe();

		virtual bool feedPipeDataToDrivers();
	};
}

#endif