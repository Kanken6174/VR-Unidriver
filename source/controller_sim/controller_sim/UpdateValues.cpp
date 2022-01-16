#include "DoMoDriver.h"

/**
* Met � jour les valeurs de position, de rotation et de latence d'un driver (appareil), et renvoie les valeurs inutilis�es
*/
vector<string> DoMoDriver::UpdateInternalValuesFromPipedData(string pipedData) {
	vector<string> ComponentData = utilities::split(pipedData, '|');

	int LatencyData = utilities::stringToInt(utilities::getFirstAndRemoveFromVector(ComponentData));
	HmdQuaternion_t* rotationOfDevice = utilities::stringToQuaternion(utilities::getFirstAndRemoveFromVector(ComponentData), '_');

	this->DeviceRotation = rotationOfDevice;


	/*	//Le shadowing, PLUS TARD
	TrackedDevicePose_t devicesPosesArray[1024];
	VRServerDriverHost()->GetRawTrackedDevicePoses(0, devicesPosesArray,1024);	//supporte jusqu'� 100 appareils, on demande leur position pour trouver celui qu'on veut shadow

	for(TrackedDevicePose_t device : devicesPosesArray)
		device.
	*/

	//pour l'instant la position sera fixe
	this->X = 0;
	this->Y = 0;
	this->Z = 0;	//les offsets sont d�j� en place donc �a mettra la manette � la place de la main droite

	if (DoMoDriver::deviceID != vr::k_unTrackedDeviceIndexInvalid)
	{
		vr::VRServerDriverHost()->TrackedDevicePoseUpdated(DoMoDriver::deviceID, GetPoseProvided(), sizeof(DriverPose_t));
	}
	else {
		DriverLog("Invalid DeviceID, skipping pose update...");
	}

	return ComponentData;
}