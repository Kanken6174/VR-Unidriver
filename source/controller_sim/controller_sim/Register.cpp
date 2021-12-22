#include "controller_sim.h"

EVRInputError VRcomponent::registerSelf() {
	EVRInputError ER = vr::EVRInputError::VRInputError_None;
	switch (sclType)
	{
	case ABSOLUTE_T:
		ER = vr::VRDriverInput()->CreateScalarComponent(parentHandle, inputPath.c_str(), &handle, EVRScalarType::VRScalarType_Absolute, JOYSTICK);
		DriverLog("Scalar component has been registered");
		break;
	case RELATIVE_T:
		ER = vr::VRDriverInput()->CreateScalarComponent(parentHandle, inputPath.c_str(), &handle, EVRScalarType::VRScalarType_Absolute, TRIGGER);
		DriverLog("Scalar component has been registered");
		break;
	case DIGITAL:

		ER = vr::VRDriverInput()->CreateBooleanComponent(parentHandle, inputPath.c_str(), &(VRcomponent::handle));

		DriverLog((std::string("Done, returned error is : ") + std::to_string((int)ER)).c_str());
		break;
	case HAPTIC:	//haptic components can't be updated, they will produce an event on haptic output
		ER = vr::VRDriverInput()->CreateHapticComponent(parentHandle, inputPath.c_str(), &handle);
		break;
	case SKELETAL:
		ER = vr::VRDriverInput()->CreateSkeletonComponent(parentHandle, inputPath.c_str(), "/skeleton/hand/right", "", vr::VRSkeletalTracking_Full, NULL, 0, &handle);//bad
		break;
	default:	//stub mode
		VRInputComponentHandle_t localhandle = -1;
		ER = vr::VRDriverInput()->CreateBooleanComponent(parentHandle, inputPath.c_str(), &localhandle);
		handle = localhandle;
		DriverLog("Registered stub boolean component with parent handle %d, inPath %s, got handle %d from default %d", parentHandle, inputPath.c_str(), handle, localhandle);
		break;
	}
	return ER;
}