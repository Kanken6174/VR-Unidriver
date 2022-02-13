#include "DoMoDriver.h"

/**
	*Cette fonction gère la mise à jour des valeurs d'entrée à chaque frame du jeu
	*/
void DoMoDriver::RunFrameStub()
{
	if (DoMoDriver::deviceID != vr::k_unTrackedDeviceIndexInvalid)
	{
		vr::VRServerDriverHost()->TrackedDevicePoseUpdated(DoMoDriver::deviceID, GetPoseStubmode(), sizeof(DriverPose_t));
	}
	else {
		DriverLog("Invalid DeviceID, skipping pose update...");
	}
	if (components.size() <= 0) { DriverLog("No components on device, skipping..."); return; }

	for (VRcomponent* component : DoMoDriver::components) {
		component->setLastLatency(lastLatency);
		component->UpdateSelf();
	}
}

void DoMoDriver::RunFrameRaw(string raw)
{
 	vector<string> componentData = this->UpdateInternalValuesFromPipedData(raw);

	if (components.size() <= 0) { DriverLog("No components on device, skipping..."); return; }

	int index = 2;
	for (VRcomponent* component : DoMoDriver::components) {
		component->UpdateSelf(componentData[index]);
		index++;
		if (index > components.size())
			return;
	}
}