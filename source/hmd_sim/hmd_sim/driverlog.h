//========= Copyright Valve Corporation ============//

#ifndef DRIVERLOG_H
#define DRIVERLOG_H

#pragma once

#include <string>
#include <openvr_driver.h>
#include <vector>	//prend la lib des vecteurs
#include <thread>	//multithreading
#include <chrono>	//heure/temps

struct Quaternion
{
    double w, x, y, z;
};

#include <windows.h>	//si sur windows, on inclut le header du système windows



// --------------------------------------------------------------------------
// Purpose: Write to the log file only in debug builds
// --------------------------------------------------------------------------
extern void DriverLog(const char* pchFormat, ...);
extern void DebugDriverLog(const char* pchFormat, ...);


extern bool InitDriverLog(vr::IVRDriverLog* pDriverLog);
extern void CleanupDriverLog();

// --------------------------------------------------------------------------
// Purpose: Simpler overview
// --------------------------------------------------------------------------
vr::HmdQuaternion_t ToQuaternion(double yaw, double pitch, double roll);



#endif // DRIVERLOG_H
