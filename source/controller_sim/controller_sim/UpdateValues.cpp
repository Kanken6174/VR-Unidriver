#include "DoMoDriver.h"

/**
* Met à jour les valeurs de position, de rotation et de latence d'un driver (appareil), et renvoie les valeurs inutilisées
*/
vector<string> DoMoDriver::UpdateInternalValuesFromPipedData(string pipedData) {
	vector<string> ComponentData = utilities::split(pipedData, '|');

	this->lastLatency = std::stol(ComponentData[0]);
	this->DeviceRotation = utilities::stringToQuaternion(ComponentData[1], '_');


	/*	//Le shadowing, PLUS TARD
	TrackedDevicePose_t devicesPosesArray[1024];
	VRServerDriverHost()->GetRawTrackedDevicePoses(0, devicesPosesArray,1024);	//supporte jusqu'à 100 appareils, on demande leur position pour trouver celui qu'on veut shadow

	for(TrackedDevicePose_t device : devicesPosesArray)
		device.
	*/

	//pour l'instant la position sera fixe
	this->X = 0;
	this->Y = 0;
	this->Z = 0;	//les offsets sont déjà en place donc ça mettra la manette à la place de la main droite

	if (DoMoDriver::deviceID != vr::k_unTrackedDeviceIndexInvalid)
	{
		vr::VRServerDriverHost()->TrackedDevicePoseUpdated(DoMoDriver::deviceID, GetPoseProvided(), sizeof(DriverPose_t));
	}
	else {
		DriverLog("Invalid DeviceID, skipping pose update...");
	}

	return ComponentData;
}

void DoMoDriver::setLastLatency(long latency)
{
	lastLatency = latency;
}