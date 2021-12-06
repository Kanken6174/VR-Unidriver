#ifndef controller_sim // include guard
#define controller_sim

#include "entry_point.h"
#include "driverlog.h"  //inclut aussi openvr.h

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
* définitions de clés d'api, cela correspond à des numéros définis dans openVR.h,
* Ils permettent de modifier des valeurs d'options liées au casque à traver l'api
* 
* Il en existe bien plus que ça
*/
static const char* const k_pch_hmd_Section = "hmd_sim";
static const char* const k_pch_hmd_SerialNumber_String = "serialNumber";
static const char* const k_pch_hmd_ModelNumber_String = "modelNumber";
static const char* const k_pch_hmd_WindowX_Int32 = "windowX";
static const char* const k_pch_hmd_WindowY_Int32 = "windowY";
static const char* const k_pch_hmd_WindowWidth_Int32 = "windowWidth";
static const char* const k_pch_hmd_WindowHeight_Int32 = "windowHeight";
static const char* const k_pch_hmd_RenderWidth_Int32 = "renderWidth";
static const char* const k_pch_hmd_RenderHeight_Int32 = "renderHeight";
static const char* const k_pch_hmd_SecondsFromVsyncToPhotons_Float = "secondsFromVsyncToPhotons";
static const char* const k_pch_hmd_DisplayFrequency_Float = "displayFrequency";

/**
* maths.h functions and definitions
* used mainly for mathematic angle conversions
*/
struct Quaternion
{
    double w, x, y, z;
};

vr::HmdQuaternion_t ToQuaternion(double yaw, double pitch, double roll);

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

	//le type VRInputComponentHandle_t est juste un uint64_t derrière
	vr::VRInputComponentHandle_t HandleDictionnary[100] = { 0 };	//un tableau de handles- 0 = k_ulInvalidInputComponentHandle dans openvr.h
	std::string inputPathDictionnary[100] = { " " };	//un tableau de chemins SVR, type /input/machin/truc
	int DictionnaryIndex = 0;

public:
	DoMoDriver();
	virtual ~DoMoDriver();
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

#endif controller_sim