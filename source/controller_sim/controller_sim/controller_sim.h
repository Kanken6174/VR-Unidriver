#include "entry_point.h"
#include "driverlog.h"  //inclut aussi openvr.h
#include "VRComponent.h"

#include <string>
#include <vector>	//prend la lib des vecteurs
#include <thread>	//multithreading
#include <chrono>	//heure/temps
#include <stdio.h>
#include <stdarg.h>
#include <windows.h>	//si sur windows, on inclut le header du système windows
#include <WinUser.h> //requis pour les hooks de clavier

using namespace vr;

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
	vr::TrackedDeviceIndex_t deviceID;	//m_unObjectId dans la doc
	vr::PropertyContainerHandle_t deviceContainer;	//m_ulpropertyContainer dans la doc

	std::string m_sSerialNumber = "DoMoDriver";	//le nom de l'appareil
	std::string NombreDeModele = "V0.1";	//le numéro de série du driver (ici de version)

	std::string inputPathDictionnary[12] = {""};	//un tableau de chemins SVR, type /input/machin/truc
	int componentType[12] = {0};
	int DictionnaryIndex = 0;
	VRcomponent components[];

public:
	DoMoDriver();
	virtual ~DoMoDriver();
	//Ces 4 fonctions servent juste à factoriser celles données par openVR pour modifier des valeurs
	virtual void setStrProperty(vr::ETrackedDeviceProperty SVRproperty, std::string value);
	virtual void setInt32Property(vr::ETrackedDeviceProperty SVRproperty, int32_t value);
	virtual void setUInt64Property(vr::ETrackedDeviceProperty SVRproperty, uint64_t value);
	virtual void setBoolProperty(vr::ETrackedDeviceProperty SVRproperty, bool value);

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
	DoMoDriver doMoDriver;

public:
	virtual EVRInitError Init(vr::IVRDriverContext* pDriverContext);
	virtual void Cleanup();

	virtual const char* const* GetInterfaceVersions();
	virtual void RunFrame();
	virtual bool ShouldBlockStandbyMode();
	virtual void EnterStandby();
	virtual void LeaveStandby();
};
