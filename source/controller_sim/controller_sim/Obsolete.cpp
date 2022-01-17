/**
* @author Yorick Geoffre
* @brief defines obsolete methods related to device activation
* @version 0.7
* @date 22/12/2021
*/

#include "DoMoDriver.h"

EVRInitError DoMoDriver::ObsoleteActivation(vr::TrackedDeviceIndex_t unObjectId) {
	DriverLog("Obsolete activate method called...\n");
	DoMoDriver::deviceID = unObjectId;	//on assigne l'id de cet appareil à partir de celui donné par le système OVR
	DriverLog(("DoMoCap has been assigned the DeviceIndex: " + std::to_string((uint32_t)unObjectId) + "\n").c_str()); // je sais, c'est horrible
	DoMoDriver::deviceContainer = vr::VRProperties()->TrackedDeviceToPropertyContainer(deviceID);	//on récupère le handle de notre appareil
	DriverLog(("DoMoCap has been assigned the propertyContainer: " + std::to_string((uint64_t)deviceID) + "\n").c_str());

	if (inputPathDictionnary.size() == componentType.size()) {
		for (int i = 0; i != inputPathDictionnary.size(); i++) {	//std::string inputPath : DoMoDriver::inputPathDictionnary
			VRcomponent* addme = new VRcomponent(inputPathDictionnary[i], deviceContainer, componentType[i]);
			DoMoDriver::components.push_back(addme);
			DriverLog("Added DIGITAL component to device");
		}
	}
	else {
		DriverLog("Error, input path and component type vector sizes mismatched, skipping component creation...");
		return EVRInitError::VRInitError_Init_MismatchedRuntimes;
	}


	DriverLog((std::string("Post-activation, registering components...")).c_str());
	return EVRInitError::VRInitError_None;
}