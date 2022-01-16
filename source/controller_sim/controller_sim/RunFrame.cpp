#include "DoMoDriver.h"

/**
	*Cette fonction g�re la mise � jour des valeurs d'entr�e � chaque frame du jeu
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

	for (VRcomponent* component : DoMoDriver::components)
		component->UpdateSelf();
}

void DoMoDriver::RunFrameRaw(string raw)
{
 	vector<string> componentData = this->UpdateInternalValuesFromPipedData(raw);

	if (components.size() <= 0) { DriverLog("No components on device, skipping..."); return; }

	for (VRcomponent* component : DoMoDriver::components)
		component->UpdateSelf();
}

void DoMoDriver::RunFrameProvided(HmdQuaternion_t poseRotation, vector<double> posePosition, vector<string> Componentdata) {
	if (DoMoDriver::deviceID != vr::k_unTrackedDeviceIndexInvalid)
	{
		vr::VRServerDriverHost()->TrackedDevicePoseUpdated(DoMoDriver::deviceID, GetPoseStubmode(), sizeof(DriverPose_t));
	}
	else {
		DriverLog("Invalid DeviceID, skipping pose update...");
	}
	if (components.size() <= 0) { DriverLog("No components on device, skipping..."); return; }

	else {
		std::string responsabilityChain = "";
		for (VRcomponent* component : DoMoDriver::components)
			if (!(component->UpdateSelf(&responsabilityChain))) {	//on a un pattern de cha�ne de repsonsabilit� ici, chanque composant prend sa part de string
				DriverLog("An error has occured in the responsability chain of the components, string may be missing parts.");
				return;	//si une erreur a eu lieu (typique: le string n'a plus de ressources disponibles), on renvoie � steamvr sans planter.
			}
	}
}