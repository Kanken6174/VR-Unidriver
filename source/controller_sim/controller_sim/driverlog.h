//========= Copyright Valve Corporation ============//

#ifndef DRIVERLOG_H
#define DRIVERLOG_H

#include <openvr_driver.h>


// --------------------------------------------------------------------------
// Purpose: Write to the log file only in debug builds
// --------------------------------------------------------------------------
extern void DriverLog(const char* pchFormat, ...);
extern void DebugDriverLog(const char* pchFormat, ...);


extern bool InitDriverLog(vr::IVRDriverLog *pDriverLog);
extern void CleanupDriverLog();



#endif // DRIVERLOG_H
