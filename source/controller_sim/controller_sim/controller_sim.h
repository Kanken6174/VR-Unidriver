/**
* @author Yorick Geoffre
* @brief this file holds the declaration of both the device driver and the server driver (server has one or more devices which has one or more components)
* @version 0.5
* @date 16/12/2021
*/
#pragma once

#include "DataDispatcher.h"

#define ABSOLUTE_S vr::VRScalarType_Absolute	//input qui n'est pas relative, donc pas une souris ou trackball, plus joystick

#define TRIGGER vr::VRScalarUnits_NormalizedOneSided	//0 à 1
#define JOYSTICK vr::VRScalarUnits_NormalizedTwoSided	// -1 à 1
#define makeDigital CreateBooleanComponent
#define makeAnalog CreateScalarComponent
#define makeHaptic CreateHapticComponent
#define updateAn UpdateScalarComponent
#define updateBool UpdateBooleanComponent
#define updatehapt UpdatehapticComponent


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
	atomic<bool> inited = false;
	atomic<bool> workThreadRunning = false;
	thread workthread;
	DataDispatcher* serverDispatcher = nullptr;	//sera bloquant tant que la communication ne sera pas établie

	virtual void RegisterInternalDrivers();

public:
	virtual EVRInitError Init(vr::IVRDriverContext* pDriverContext);
	virtual void Cleanup();

	virtual const char* const* GetInterfaceVersions();
	virtual void RunFrame();
	virtual bool ShouldBlockStandbyMode();
	virtual void EnterStandby();
	virtual void LeaveStandby();

	virtual void beginThreadedWork();
	virtual int doThreadedWork();
	virtual void stopThreadedWork();

	virtual bool shouldWorkThreadRun();
};

namespace utilities {
	vector<DriverDataTemplate*> ReadConfigAndBuildDrivers();
	wstring ExePath();
	vector<DoMoDriver*> makeDriversFromTemplates(vector<DriverDataTemplate*> DriverTemplates);
}