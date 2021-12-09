#include "driverlog.h"
#include <openvr_driver.h>

#define ABSOLUTE_T 0	//input qui n'est pas relative, donc pas une souris ou trackball, plus joystick
#define DIGITAL 2
#define HAPTIC 3
#define SKELETAL 4
#define TRIGGER vr::VRScalarUnits_NormalizedOneSided	//0 à 1
#define JOYSTICK vr::VRScalarUnits_NormalizedTwoSided	// -1 à 1
#define makeDigital CreateBooleanComponent
#define makeAnalog CreateScalarComponent
#define makeHaptic CreateHapticComponent
#define updateAn UpdateScalarComponent
#define updateBool UpdateBooleanComponent
#define updatehapt UpdatehapticComponent

class VRcomponent
{
private:
	std::string inputPath = "";
	vr::VRInputComponentHandle_t handle;
	vr::PropertyContainerHandle_t parentHandle;
	int sclType = 0;
	bool state = false;
public:
	VRcomponent();
	VRcomponent(std::string inputPath, vr::PropertyContainerHandle_t parentHandle, int sclType);	//constructeur
	virtual vr::VRInputComponentHandle_t GetHandle();
	virtual vr::EVRInputError registerSelf();
	virtual vr::EVRInputError UpdateSelf(bool value);
	virtual vr::EVRInputError UpdateSelf(float value);
	virtual vr::EVRInputError UpdateSelf(vr::VRBoneTransform_t* hand, int size);	//size est mis à 31 si non-précisé
};
