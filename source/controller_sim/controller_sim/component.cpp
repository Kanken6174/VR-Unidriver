#include "VRComponent.h"

using namespace vr;

	VRcomponent::VRcomponent() {		//ne devrait jamais être appellé
		DriverLog("BAD_COMPONENT_CALL\n");
		this->parentHandle = 999999;	//error
		this->inputPath = "";
	}

	VRcomponent::VRcomponent(vr::PropertyContainerHandle_t parentHandle,ComponentDataTemplate componentData) {
		this->parentHandle = parentHandle;	//handle du parent (uint)
		this->localData = componentData;
		this->inputPath = componentData.inputPath;
		this->sclType = componentData.inputType;
		DriverLog("VR component has been created");
	}

	VRcomponent::VRcomponent(std::string inputPath, vr::PropertyContainerHandle_t parentHandle, int sclType) {
		this->parentHandle = parentHandle;	//handle du parent (uint)
		this->inputPath = inputPath;//input path
		this->sclType = sclType;	//type d'input
		DriverLog("VR component has been created");
	}

	VRInputComponentHandle_t VRcomponent::GetHandle() {
		return handle;
	}

	EVRInputError VRcomponent::registerSelf() {
		EVRInputError ER = vr::EVRInputError::VRInputError_None;
		switch (sclType)
		{
		case ABSOLUTE_T:
			ER = vr::VRDriverInput()->CreateScalarComponent(parentHandle, inputPath.c_str(), &handle, EVRScalarType::VRScalarType_Absolute, JOYSTICK);
			DriverLog("Scalar component has been registered");
		case DIGITAL:

			ER = vr::VRDriverInput()->CreateBooleanComponent(parentHandle, inputPath.c_str(), &(VRcomponent::handle));

			DriverLog((std::string("Done, returned error is : ") + std::to_string((int)ER)).c_str());
			break;
		case HAPTIC:	//haptic components can't be updated, they will produce an event on haptic output
			ER = vr::VRDriverInput()->CreateHapticComponent(parentHandle, inputPath.c_str(), &handle);
			break;
		case SKELETAL:
			ER = vr::VRDriverInput()->CreateSkeletonComponent(parentHandle, inputPath.c_str(), "/skeleton/hand/right", "", vr::VRSkeletalTracking_Full,NULL,0,&handle);//bad
			break;
		default:	//stub mode

			ER = vr::VRDriverInput()->CreateBooleanComponent(parentHandle, inputPath.c_str(), &(VRcomponent::handle));
			DriverLog("Registered stub boolean component");
			break;
		}
		return ER;
	}

	EVRInputError VRcomponent::UpdateSelf() {	//mode stub clavier
		bool value = (0x8000 & GetAsyncKeyState(sclType)) != 0;
		if (sclType != DIGITAL)
			return vr::EVRInputError::VRInputError_WrongType;
		if (state != value) {
			state = !state;
			EVRInputError ER = vr::VRDriverInput()->UpdateBooleanComponent(handle, value, 0);

			DriverLog((std::string("Key state changed! handle = ") + std::to_string((uint32_t)handle) + std::string(" error code = ") + std::to_string((int)ER)).c_str());
			return ER;
		}
		else
			return EVRInputError::VRInputError_None;
	}

	EVRInputError VRcomponent::UpdateSelf(bool value) {
		if (sclType != DIGITAL)
			return vr::EVRInputError::VRInputError_WrongType;
		if (state != value) {
			state = !state;
			EVRInputError ER =vr::VRDriverInput()->UpdateBooleanComponent(handle, value, 0);

			DriverLog((std::string("Key state changed! handle = ") + std::to_string((uint32_t)handle) + std::string(" error code = ")+ std::to_string((int)ER)).c_str());
			return ER;
		}
		else
			return EVRInputError::VRInputError_None;
	}

	EVRInputError VRcomponent::UpdateSelf(float value) {
		if (sclType != ABSOLUTE_T || value > 1 || value <-1)
			return vr::VRInputError_WrongType;
		return vr::VRDriverInput()->UpdateScalarComponent(handle, value, 0);
	}

	EVRInputError VRcomponent::UpdateSelf(vr::VRBoneTransform_t* hand, int size = 31) {
		return vr::VRDriverInput()->UpdateSkeletonComponent(handle,vr::EVRSkeletalMotionRange::VRSkeletalMotionRange_WithoutController, hand, size);
	}