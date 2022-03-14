/**
* @author Yorick Geoffre
* @brief this file holds the declaration of the main server driver, which possesses all other devices and subsequent components, and passes the pointers to SteamVR
* @version 0.7
* @date 16/12/2021
*/

#include "controller_sim.h"

using namespace vr;



/**
* reference: https://github.com/ValveSoftware/openvr/wiki/IServerTrackedDeviceProvider_Overview
* Il s'agit du serveur qui va contrôler les différents appareils, car il peut y en avoir plusieurs par
* serveur.
*/
EVRInitError Controller_simDriverServer::Init(vr::IVRDriverContext* pDriverContext)
{
	srand(time(NULL)); // Seed the time
	VR_INIT_SERVER_DRIVER_CONTEXT(pDriverContext);	//une fonction définie dans openvr_driver.h
	InitDriverLog(vr::VRDriverLog());	//initialise le logging d'informations visible sur la console web

	DriverLog("log inited\n");;

	DriverTemplates = utilities::ReadConfigAndBuildDrivers();
	Drivers = utilities::makeDriversFromTemplates(DriverTemplates);
	DriverLog("driver(s) inited\n");
	RegisterInternalDrivers();
	DriverLog("driver(s) registered");
	DriverLog("Connecting to named pipe...");
	this->serverDispatcher = new DataDispatcher();
	DriverLog("Successfully connected!");
	inited = true;
	this->beginThreadedWork();
	return VRInitError_None;
}


void Controller_simDriverServer::RegisterInternalDrivers() {
	for (DoMoDriver* driver : *Controller_simDriverServer::Drivers) {
		bool success = vr::VRServerDriverHost()->TrackedDeviceAdded(driver->GetSerialNumber().c_str(), vr::TrackedDeviceClass_Controller, driver);
		if (success)
			DriverLog("driver registered successfully\n");
		else
			DriverLog("Failed to register driver");
	}
}

void Controller_simDriverServer::Cleanup()
{
	this->stopThreadedWork();
	inited = false;
	CleanupDriverLog();
	for (DoMoDriver* driver : *Controller_simDriverServer::Drivers)
		driver->~DoMoDriver();	//appel de destructeur
}

const char* const* Controller_simDriverServer::GetInterfaceVersions()
{
	return vr::k_InterfaceVersions;
}

void Controller_simDriverServer::RunFrame()
{
}
bool Controller_simDriverServer::ShouldBlockStandbyMode() { return false; }
void Controller_simDriverServer::EnterStandby() {/*standby code for the gloves here??*/ }
void Controller_simDriverServer::LeaveStandby() {/*Wake up for the gloves here?*/ }

void Controller_simDriverServer::beginThreadedWork()
{
	DriverLog("Starting work thread...");
	this->workThreadRunning = true;
	this->workthread = thread(&Controller_simDriverServer::doThreadedWork,this);
	DriverLog("Done starting work thread.");
}

int Controller_simDriverServer::doThreadedWork()
{
	DriverLog("Workthread running");
	DriverLog("Calling feed with %d drivers", this->Drivers->size());
	bool ran = false;
	int z = 0;
	//clock_t t;
	while (shouldWorkThreadRun()) {
		//t = clock();
		this->serverDispatcher->feedPipeDataToDrivers(this->Drivers);	//prod mode
		//t = clock() - t;
		//DriverLog("full cycle time : % d ms", t);
		//Sleep(5);
		if (z > 3000) {
				utilities::logAllDevices();
				ran = true;
				z = 0;
		}
		else {
			z++;
		}
	}
	DriverLog("Workthread stopped");
	return 0;
}

void Controller_simDriverServer::stopThreadedWork()
{
	DriverLog("Stopping threaded work...");
	this->workThreadRunning = false;
}

bool Controller_simDriverServer::shouldWorkThreadRun()
{
	return this->workThreadRunning;
}



/**
* La fonction qui sera exportée vers OpenVR, il s'agit de
* notre point d'entrée! (int main() en gros)
*
* Elle va récupérer des pointeurs vers des classes prédéfinies pour les charger dans SVR
*/
HMD_DLL_EXPORT FUNCTION_POINTER HmdDriverFactory(const char* pInterfaceName, int* pReturnCode)
{
	if (0 == strcmp("IServerTrackedDeviceProvider_004", pInterfaceName))	//on vérifie que le nom d'interface correspond
	{
		Controller_simDriverServer* controller_simServer = new Controller_simDriverServer();
		return controller_simServer;	//on renvoie l'addresse de la classe du serveur du driver
	}

	if (0 == strcmp(IVRWatchdogProvider_Version, pInterfaceName))
	{
		return NULL;	//on a pas de watchdog dans ce driver, comme on fait pas tourner de code en arrière-plan
	}

	if (pReturnCode)
		*pReturnCode = 105;	//cette valeur correspond à VRInitError_Init_InterfaceNotFound dans openvr_driver.h enum

	return NULL;
}