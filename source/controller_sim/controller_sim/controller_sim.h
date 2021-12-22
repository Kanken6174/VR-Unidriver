/**
* @author Yorick Geoffre
* @brief this file holds the declaration of both the device driver and the server driver (server has one or more devices which has one or more components)
* @version 0.5
* @date 16/12/2021
*/
#pragma once

#include "VRComponent.h"

#define ABSOLUTE_S vr::VRScalarType_Absolute	//input qui n'est pas relative, donc pas une souris ou trackball, plus joystick

#define TRIGGER vr::VRScalarUnits_NormalizedOneSided	//0 à 1
#define JOYSTICK vr::VRScalarUnits_NormalizedTwoSided	// -1 à 1
#define makeDigital CreateBooleanComponent
#define makeAnalog CreateScalarComponent
#define makeHaptic CreateHapticComponent
#define updateAn UpdateScalarComponent
#define updateBool UpdateBooleanComponent
#define updatehapt UpdatehapticComponent

/**
* maths.h functions and definitions
* used mainly for mathematic angle conversions
*/
struct Quaternion
{
    double w, x, y, z;
};

vr::HmdQuaternion_t ToQuaternion(double yaw, double pitch, double roll);

/*
-------------------------------------------------------CLASSE DRIVER---------------------------------------------------
*/

/*Cette classe représente un appareil tracké (implémente ITrackedDeviceServerDriver), il a une position et une rotation,
* et peut 
*/
class DoMoDriver : public vr::ITrackedDeviceServerDriver
{
private:
	vr::TrackedDeviceIndex_t deviceID = vr::k_unTrackedDeviceIndexInvalid;	//m_unObjectId dans la doc
	vr::PropertyContainerHandle_t deviceContainer = vr::k_ulInvalidPropertyContainer;	//m_ulpropertyContainer dans la doc

	std::string m_sSerialNumber = "DoMoDriver";	//le nom de l'appareil
	std::string DeviceRender = "oculus_cv1_controller_right";	//à la fois le "modèle" de l'appareil, mais aussi son modèle 3d (rendermodels)
																//ici on vole le modèle 3d de la manette d'oculus

	DriverDataTemplate localData;	//version moderne

	std::vector <VRcomponent*> components;	//un vecteur de pointeurs vers des VRcomponent
	double yaw = 0, pitch = 0, roll = 0, X = 0, Y = 0;

	bool ObsoleteMode = true;	//définit la version de la méthode d'activation à utiliser
	//Obsolètes, sauf si utilisation du driver sans les dataTemplates
	std::vector <std::string> inputPathDictionnary;//un tableau de chemins SVR, type /input/machin/truc
	std::vector <int> componentType;

public:
	DoMoDriver(DriverDataTemplate ddt);
	DoMoDriver(std::string name);
	DoMoDriver(std::string name, std::vector<int> compoTypes, std::vector<std::string> compoPaths);

	virtual ~DoMoDriver();

	//Ces 4 fonctions servent juste à factoriser celles données par openVR pour modifier des valeurs
	virtual void setStrProperty(vr::ETrackedDeviceProperty SVRproperty, std::string value);
	virtual void setInt32Property(vr::ETrackedDeviceProperty SVRproperty, int32_t value);
	virtual void setUInt64Property(vr::ETrackedDeviceProperty SVRproperty, uint64_t value);
	virtual void setBoolProperty(vr::ETrackedDeviceProperty SVRproperty, bool value);

	virtual EVRInitError ModernActivation(vr::TrackedDeviceIndex_t unObjectId);
	virtual EVRInitError ObsoleteActivation(vr::TrackedDeviceIndex_t unObjectId);
	virtual void registerProperties(vr::TrackedDeviceIndex_t unObjectId);

	//fonctions requises par l'interface ITrackedDeviceServerDriver, commes données dans le sample
	virtual EVRInitError Activate(vr::TrackedDeviceIndex_t unObjectId);
	virtual void Deactivate();
	virtual void EnterStandby();
	virtual void* GetComponent(const char* pchComponentNameAndVersion);
	virtual void PowerOff();
	virtual void DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize);
	/*Cette fonction gère la position (rotation quaternionique et position par vecteur) de l'objet,
	* qrotation est responsable de l'angle et Vecposition[3] de la position.
	*/
	virtual void GetKeypresses();
	virtual DriverPose_t GetPose();
	/**
	*Cette fonction gère la mise à jour des valeurs d'entrée à chaque frame du jeu
	*/
	virtual void RunFrame();
	virtual std::string GetSerialNumber();
};

/*
-------------------------------------------------------CLASSE SERVEUR---------------------------------------------------
*/
/*Cette classe possède tous les drivers et intéragit avec SteamVR
*/
class Controller_simDriverServer : public IServerTrackedDeviceProvider
{
private:
	vector<DriverDataTemplate*> DriverTemplates;
	vector<DoMoDriver*> Drivers;
	bool inited = false;
	virtual void RegisterInternalDrivers();

public:
	virtual EVRInitError Init(vr::IVRDriverContext* pDriverContext);
	virtual void Cleanup();

	virtual const char* const* GetInterfaceVersions();
	virtual void RunFrame();
	virtual bool ShouldBlockStandbyMode();
	virtual void EnterStandby();
	virtual void LeaveStandby();
};

//-----------------------------------------Utilitaires---------------------------------------------

namespace utilities {
	vector<DriverDataTemplate*> ReadConfigAndBuildDrivers();
	wstring ExePath();
	vector<DoMoDriver*> makeDriversFromTemplates(vector<DriverDataTemplate*> DriverTemplates);
}