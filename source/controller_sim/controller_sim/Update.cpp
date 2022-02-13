#include "VRComponent.h"

EVRInputError VRcomponent::UpdateSelf(string providedValue) {
	EVRInputError toReturn = VRInputError_None;
	switch (sclType) {
	case ABSOLUTE_T: case RELATIVE_T:
		//DriverLog(providedValue.c_str());
		toReturn = UpdateSelf(utilities::stringToFloat(providedValue));
		break;
	case DIGITAL:
		toReturn = UpdateSelf((providedValue=="1")?true:false);
		break;
	case SKELETAL:
		//toReturn + UpdateSelf();
		break;
	case HAPTIC:
		break;// HAPTIC est un composant de sortie et pas d'entrée, on l'ignore
	default:
		toReturn = VRInputError_WrongType;
		break;
	}

	if (toReturn != EVRInputError::VRInputError_None)
		DriverLog("Update of component with path %s had an error for value %s", this->inputPath, providedValue);

	return toReturn;
}

void VRcomponent::setLastLatency(long latency){
	lastLatency = latency;
}

EVRInputError VRcomponent::UpdateSelf(bool value) {
	if (sclType != DIGITAL)
		return vr::EVRInputError::VRInputError_WrongType;

	EVRInputError ER = vr::VRDriverInput()->UpdateBooleanComponent(handle, value, lastLatency);

	//DriverLog((std::to_string(value).c_str()));
	return ER;
}

EVRInputError VRcomponent::UpdateSelf(float value) {
	if ((sclType != ABSOLUTE_T && sclType != RELATIVE_T) || value > 1 || value < -1) {
		DriverLog("Value was incorrect for type %d, got value %f",sclType,value);
		return vr::VRInputError_WrongType;
	}

	return vr::VRDriverInput()->UpdateScalarComponent(handle, value, lastLatency);
}

EVRInputError VRcomponent::UpdateSelf(vr::VRBoneTransform_t* hand, int size = 31) {
	EVRInputError ER = vr::VRDriverInput()->UpdateSkeletonComponent(handle, vr::EVRSkeletalMotionRange::VRSkeletalMotionRange_WithoutController, hand, size);
	return ER;
}

//-------------------------------------------------------------Mode stub clavier-------------------------------------------------------------------------------------

EVRInputError VRcomponent::UpdateSelf() {
	DriverLog("Called update float on component of type stub");
	bool value = ((0x8000 & GetAsyncKeyState(sclType)) != 0);

	if (keyState != value) {
		keyState = !keyState;
		EVRInputError ER = vr::VRDriverInput()->UpdateBooleanComponent(handle, value, 0);

		//DriverLog((std::string("Key state changed! handle = ") + std::to_string((uint32_t)handle) + std::string(" error code = ") + std::to_string((int)ER)).c_str());
		return ER;
	}
	else
		return EVRInputError::VRInputError_None;
}