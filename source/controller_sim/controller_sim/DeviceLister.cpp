#include "utilities.h"
#include "driverlog.h"

namespace utilities {
	void logAllDevices() {
		TrackedDevicePose_t devicesPosesArray[vr::k_unMaxTrackedDeviceCount];
		VRServerDriverHost()->GetRawTrackedDevicePoses(0, devicesPosesArray, vr::k_unMaxTrackedDeviceCount);	//supporte jusqu'à 100 appareils, on demande leur position pour trouver celui qu'on veut shadow
		DriverLog("Looking for devices...");
		char pchname[1024];
		for (vr::TrackedDeviceIndex_t i = 0; i < vr::k_unMaxTrackedDeviceCount; i++) {
			if (devicesPosesArray[i].bPoseIsValid) {
				VRDriverManager()->GetDriverName(i, pchname, 1024);
				DriverLog("device found at index %d with name %s", i, pchname);
			}
		}
		DriverLog("Done looking for devices");
		
	}
}