/**
* @author Yorick Geoffre
* @brief defines a single component, like a joystick or a button on a device
* @version 0.3 - added dataTemplate based constructors
* @date 30/11/2021
*/

#include "VRComponent.h"

	VRcomponent::VRcomponent() {		//ne devrait jamais être appellé
		DriverLog("BAD_COMPONENT_CALL\n");
		this->parentHandle = 999999;	//error
		this->inputPath = "";
	}

	VRcomponent::VRcomponent(vr::PropertyContainerHandle_t parentHandle, ComponentDataTemplate componentData) {
		this->parentHandle = parentHandle;	//handle du parent (uint)
		DriverLog("Passed parent handle is %d", parentHandle);
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