/**
* @author Yorick Geoffre
* @brief defines a single component, like a joystick or a button on a device
* @version 0.3 - added dataTemplate based constructors
* @date 30/11/2021
*/

#include "dataObjects.h"
#include "utilities.h"

#define ABSOLUTE_T 0	//input qui n'est pas relative, donc pas une souris ou trackball, plus joystick
#define RELATIVE_T 1
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

	ComponentDataTemplate localData;	//utilisé uniquement par le constructeur du driver

	std::string inputPath = "";
	vr::VRInputComponentHandle_t handle;
	vr::PropertyContainerHandle_t parentHandle;
	int sclType = 0;

	bool keyState = false;//utilisé par le stub uniquement
public:
	VRcomponent();
	VRcomponent(vr::PropertyContainerHandle_t parentHandle, ComponentDataTemplate componentData);	//constructeur moderne
	VRcomponent(std::string inputPath, vr::PropertyContainerHandle_t parentHandle, int sclType);	//constructeur	obsolète
	virtual vr::VRInputComponentHandle_t GetHandle();
	virtual vr::EVRInputError registerSelf();

	virtual vr::EVRInputError UpdateSelf();	//mode stub, update sur sa propre valeur

	virtual vr::EVRInputError UpdateSelf(bool value);
	virtual vr::EVRInputError UpdateSelf(float value);
	virtual vr::EVRInputError UpdateSelf(vr::VRBoneTransform_t* hand, int size);	//size est mis à 31 si non-précisé

	virtual vr::EVRInputError UpdateSelf(string providedValue);
};