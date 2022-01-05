/**
* @author Yorick Geoffre
* @brief defines methods required by the ITrackedDevice interface, but they aren't actually used to the extent they should be (ignored)
* @version 0.7
* @date 22/12/2021
*/

#include "controller_sim.h"

DriverPose_t DoMoDriver::GetPose() {
	DriverPose_t err = DriverPose_t();
	DriverLog("Error, interface-inherited GetPose() was called!");
	return err;
}

string DoMoDriver::GetSerialNumber() {
	return m_sSerialNumber;
}

void DoMoDriver::Deactivate() { 
	DoMoDriver::deviceID = vr::k_unTrackedDeviceIndexInvalid;
}

void DoMoDriver::EnterStandby() {/*on pourrait stopped la collecte d'entrées du gant ici*/ }

void* DoMoDriver::GetComponent(const char* pchComponentNameAndVersion)
{
	// override this to add a component to a driver
	return NULL;
}

void DoMoDriver::PowerOff() {}

void DoMoDriver::DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize)
{
	if (unResponseBufferSize >= 1)
		pchResponseBuffer[0] = 0;
	DriverLog("No\n");
}