#ifndef VRCOMPONENT // include guard - assure une inclusion unique
#define VRCOMPONENT

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
	int sclType;

public:
	VRcomponent(std::string inputPath, vr::PropertyContainerHandle_t parentHandle);	//constructeur
	VRInputComponentHandle_t GetHandle();
	EVRInputError registerSelf();
	EVRInputError UpdateSelf(bool value);
	EVRInputError UpdateSelf(float value);

	//les méthodes liées aux composants d'entrée skelette seront ajoutés plus tard.
};

#endif VRCOMPONENT