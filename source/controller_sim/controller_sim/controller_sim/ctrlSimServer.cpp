#include "controller_sim.h"

using namespace vr;



/**
* reference: https://github.com/ValveSoftware/openvr/wiki/IServerTrackedDeviceProvider_Overview
* Il s'agit du serveur qui va contrôler les différents appareils, car il peut y en avoir plusieurs par
* serveur.
*/
	EVRInitError Controller_simDriverServer::Init(vr::IVRDriverContext* pDriverContext)
	{
		VR_INIT_SERVER_DRIVER_CONTEXT(pDriverContext);	//une fonction définie dans openvr_driver.h
		InitDriverLog(vr::VRDriverLog());	//initialise le logging d'informations visible sur la console web
		DriverLog("ctrl_sim: log inited\n");
		DoMoDriver *doMoDriver = new DoMoDriver();	//initialise no(s)[tre] driver(s)
		DriverLog("ctrl_sim: driver inited\n");
		//register ce driver auprès de SVR
		vr::VRServerDriverHost()->TrackedDeviceAdded(Controller_simDriverServer::doMoDriver.GetSerialNumber().c_str(), vr::TrackedDeviceClass_GenericTracker, doMoDriver);
		DriverLog("ctrl_sim: driver registered\n");
		return VRInitError_None;
	}

	void Controller_simDriverServer::Cleanup()
	{
		CleanupDriverLog();
		Controller_simDriverServer::doMoDriver.~DoMoDriver();
	}

	const char* const* Controller_simDriverServer::GetInterfaceVersions() 
	{ 
		return vr::k_InterfaceVersions; 
	}

	void Controller_simDriverServer::RunFrame()
	{
		Controller_simDriverServer::doMoDriver.RunFrame();

		vr::VREvent_t vrEvent;
		while (vr::VRServerDriverHost()->PollNextEvent(&vrEvent, sizeof(vrEvent)))
		{
		}
	}
	bool Controller_simDriverServer::ShouldBlockStandbyMode() { return false; }
	void Controller_simDriverServer::EnterStandby() {/*standby code for the gloves here??*/}
	void Controller_simDriverServer::LeaveStandby() {/*Wake up for the gloves here?*/}

	Controller_simDriverServer controller_simServer;	//c'est global, c'est moche, c'est SteamVR


/**
* La fonction qui sera exportée vers OpenVR, il s'agit de
* notre point d'entrée! (void main() en gros)
*
* Elle va récupérer des pointeurs vers des classes prédéfinies pour les charger dans SVR
*/
HMD_DLL_EXPORT FUNCTION_POINTER HmdDriverFactory(const char* pInterfaceName, int* pReturnCode)
{
	if (0 == strcmp("IServerTrackedDeviceProvider_004", pInterfaceName))	//on vérifie que le nom d'interface correspond
	{
		return &controller_simServer;	//on renvoie l'addresse de la classe du serveur du driver
	}

	if (0 == strcmp(IVRWatchdogProvider_Version, pInterfaceName))
	{
		return NULL;	//on a pas de watchdog dans ce driver, comme on fait pas tourner de code en arrière-plan
	}

	if (pReturnCode)
		*pReturnCode = 105;	//cette valeur correspond à VRInitError_Init_InterfaceNotFound dans openvr_driver.h enum

	return NULL;
}