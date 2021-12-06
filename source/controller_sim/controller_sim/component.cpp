#include "driverlog.h"
#include "controller_sim.h"
#include "VRComponent.h"

using namespace vr;



	VRcomponent::VRcomponent(std::string inputPath, vr::PropertyContainerHandle_t parentHandle) {
		this->parentHandle = parentHandle;
		this->inputPath = inputPath;
		DriverLog("VR component has been created");
	}

	VRInputComponentHandle_t VRcomponent::GetHandle() {
		return handle;
	}

	EVRInputError VRcomponent::registerSelf() {
		EVRInputError ER = EVRInputError::VRInputError_None;
		switch (sclType)
		{
		case ABSOLUTE_T:
			ER = vr::VRDriverInput()->CreateScalarComponent(parentHandle, inputPath.c_str(), &handle, EVRScalarType::VRScalarType_Absolute, JOYSTICK);
			DriverLog("Scalar component has been registered");
		case DIGITAL:
			ER = vr::VRDriverInput()->CreateBooleanComponent(parentHandle, inputPath.c_str(), &handle);
			DriverLog("Boolean component has been registered");
			break;
		case HAPTIC:	//haptic components can't be updated, they will produce an event on haptic output
			ER = vr::VRDriverInput()->CreateHapticComponent(parentHandle, inputPath.c_str(), &handle);
			break;
		case SKELETAL:
			ER = vr::VRDriverInput()->CreateSkeletonComponent(parentHandle, inputPath.c_str(), "/skeleton/hand/right", "", vr::VRSkeletalTracking_Full,NULL,0,&handle);//bad
			break;
		default:
			break;
		}

		return ER;
	}

	EVRInputError VRcomponent::UpdateSelf(bool value) {
		if (sclType != DIGITAL)
			return vr::EVRInputError::VRInputError_WrongType;
		return vr::VRDriverInput()->UpdateBooleanComponent(handle, value, 0);
	}

	EVRInputError VRcomponent::UpdateSelf(float value) {
		if (sclType != ABSOLUTE_T || value > 1 || value <-1)
			return vr::VRInputError_WrongType;
		return vr::VRDriverInput()->UpdateScalarComponent(handle, value, 0);
	}