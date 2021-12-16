/**
* @author Valve corporation
* @brief this file holds the declaration of the driver logging related functions
* @version 0.1
* @date 16/12/2021
*/


#include <openvr_driver.h>


// --------------------------------------------------------------------------
// Purpose: Write to the log file only in debug builds
// --------------------------------------------------------------------------
extern void DriverLog(const char* pchFormat, ...);
extern void DebugDriverLog(const char* pchFormat, ...);


extern bool InitDriverLog(vr::IVRDriverLog *pDriverLog);
extern void CleanupDriverLog();

