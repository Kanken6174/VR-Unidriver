#include "controller_sim.h"

using namespace vr;



/**
* reference: https://github.com/ValveSoftware/openvr/wiki/IServerTrackedDeviceProvider_Overview
* Il s'agit du serveur qui va contrôler les différents appareils, car il peut y en avoir plusieurs par
* serveur.
*/
	EVRInitError Controller_simDriverServer::Init(vr::IVRDriverContext* pDriverContext)
	{
		VR_INIT_SERVER_DRIVER_CONTEXT(pDriverContext);
		InitDriverLog(vr::VRDriverLog());

		DoMoDriver *doMoDriver = new DoMoDriver();
		vr::VRServerDriverHost()->TrackedDeviceAdded(Controller_simDriverServer::doMoDriver.GetSerialNumber().c_str(), vr::TrackedDeviceClass_GenericTracker, doMoDriver);

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
*/
HMD_DLL_EXPORT FUNCTION_POINTER HmdDriverFactory(const char* pInterfaceName, int* pReturnCode)
{
	if (0 == strcmp("IServerTrackedDeviceProvider_004", pInterfaceName))	//on vérifie que le nom d'interface correspond
	{
		return &controller_simServer;	//on renvoie l'addresse de la classe du serveur du driver
	}

	if (pReturnCode)
		*pReturnCode = 105;	//cette valeur correspond à VRInitError_Init_InterfaceNotFound dans openvr_driver.h enum

	return NULL;
}