#include "VRComponent.h"

EVRInputError VRcomponent::UpdateSelf(string providedValue) {
	EVRInputError toReturn = VRInputError_None;
	switch (sclType) {
	case ABSOLUTE_T: case RELATIVE_T:
		toReturn = UpdateSelf(utilities::stringToFloat(providedValue));
		break;
	case DIGITAL:
		toReturn = UpdateSelf(utilities::stringToBool(providedValue));
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
	return toReturn;
}

EVRInputError VRcomponent::UpdateSelf(bool value) {
	if (sclType != DIGITAL)
		return vr::EVRInputError::VRInputError_WrongType;
	if (keyState != value) {
		keyState = !keyState;
		EVRInputError ER = vr::VRDriverInput()->UpdateBooleanComponent(handle, value, 0);

		DriverLog((std::string("Key state changed! handle = ") + std::to_string((uint32_t)handle) + std::string(" error code = ") + std::to_string((int)ER)).c_str());
		return ER;
	}
	else
		return EVRInputError::VRInputError_None;
}

EVRInputError VRcomponent::UpdateSelf(float value) {
	if (sclType == ABSOLUTE_T || sclType == RELATIVE_T || value > 1 || value < -1)
		return vr::VRInputError_WrongType;

	return vr::VRDriverInput()->UpdateScalarComponent(handle, value, 0);
}

EVRInputError VRcomponent::UpdateSelf(vr::VRBoneTransform_t* hand, int size = 31) {
	return vr::VRDriverInput()->UpdateSkeletonComponent(handle, vr::EVRSkeletalMotionRange::VRSkeletalMotionRange_WithoutController, hand, size);
}

//-------------------------------------------------------------Mode stub clavier-------------------------------------------------------------------------------------

EVRInputError VRcomponent::UpdateSelf() {
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