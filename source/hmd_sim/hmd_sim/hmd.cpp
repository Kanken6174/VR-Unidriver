//============ Copyright (c) Valve Corporation, All rights reserved. ============

#if defined(_WIN32)
#define HMD_DLL_EXPORT extern "C" __declspec( dllexport )
#define HMD_DLL_IMPORT extern "C" __declspec( dllimport )
#elif defined(__GNUC__) || defined(COMPILER_GCC) || defined(__APPLE__)	//cas apple / linux
#define HMD_DLL_EXPORT extern "C" __attribute__((visibility("default")))
#define HMD_DLL_IMPORT extern "C" 
#else
#error "Unsupported Platform."
#endif

#include "driverlog.h"	//dédié aux logs
#include "hmd.h"
using namespace vr;

double roll, pitch, yaw, X, Y, Z = 0;


inline HmdQuaternion_t HmdQuaternion_Init(double w, double x, double y, double z)	//on définit une fonction pour init un quaternion (pq? jsp lol)
{
	HmdQuaternion_t quat;
	quat.w = w;
	quat.x = x;
	quat.y = y;
	quat.z = z;
	return quat;
}



//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------

class CWatchdoghmd_sim : public IVRWatchdogProvider
{
public:
	CWatchdoghmd_sim()
	{
		m_pWatchdogThread = nullptr;
	}

	virtual EVRInitError Init(vr::IVRDriverContext* pDriverContext);
	virtual void Cleanup();

private:
	std::thread* m_pWatchdogThread;
};

CWatchdoghmd_sim g_watchdogDriverNull;


bool g_bExiting = false;

void WatchdogThreadFunction()
{
	while (!g_bExiting)
	{
		DriverLog("hmd_sim : Waiting for keyboard Y input!\n");
		// on windows send the event when the Y key is pressed.
		if ((0x8000 & GetAsyncKeyState('Y')) != 0)
		{
			DriverLog("hmd_sim : Y input FOUND! Waking driver\n");
			// Y key was pressed. 
			vr::VRWatchdogHost()->WatchdogWakeUp(vr::TrackedDeviceClass_HMD);
		}
		std::this_thread::sleep_for(std::chrono::microseconds(500));

	}
}

EVRInitError CWatchdoghmd_sim::Init(vr::IVRDriverContext* pDriverContext)
{
	VR_INIT_WATCHDOG_DRIVER_CONTEXT(pDriverContext);
	InitDriverLog(vr::VRDriverLog());
	DriverLog("hmd_sim : hmd1 has started the driver logging!!!\n");

	// Watchdog mode on Windows starts a thread that listens for the 'Y' key on the keyboard to 
	// be pressed. A real driver should wait for a system button event or something else from the 
	// the hardware that signals that the VR system should start up.
	g_bExiting = false;
	m_pWatchdogThread = new std::thread(WatchdogThreadFunction);
	if (!m_pWatchdogThread)
	{
		DriverLog("Unable to create watchdog thread\n");
		return VRInitError_Driver_Failed;
	}

	return VRInitError_None;
}


void CWatchdoghmd_sim::Cleanup()
{
	DriverLog("hmd_sim : Cleaning up before leaving!\n");
	g_bExiting = true;
	if (m_pWatchdogThread)
	{
		m_pWatchdogThread->join();
		delete m_pWatchdogThread;
		m_pWatchdogThread = nullptr;
	}

	CleanupDriverLog();
}


//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
class ChmdDeviceDriver : public vr::ITrackedDeviceServerDriver, public vr::IVRDisplayComponent
{
public:
	ChmdDeviceDriver()
	{
		DriverLog("hmd_sim : Construction du ChmdDeviceDriver en cours!\n");
		m_unObjectId = vr::k_unTrackedDeviceIndexInvalid;
		m_ulPropertyContainer = vr::k_ulInvalidPropertyContainer;

		DriverLog("Using settings values\n");
		m_flIPD = vr::VRSettings()->GetFloat(k_pch_SteamVR_Section, k_pch_SteamVR_IPD_Float);

		char buf[1024];
		vr::VRSettings()->GetString(k_pch_hmd_Section, k_pch_hmd_SerialNumber_String, buf, sizeof(buf));
		m_sSerialNumber = buf;

		vr::VRSettings()->GetString(k_pch_hmd_Section, k_pch_hmd_ModelNumber_String, buf, sizeof(buf));
		m_sModelNumber = buf;

		m_nWindowX = vr::VRSettings()->GetInt32(k_pch_hmd_Section, k_pch_hmd_WindowX_Int32);
		m_nWindowY = vr::VRSettings()->GetInt32(k_pch_hmd_Section, k_pch_hmd_WindowY_Int32);
		m_nWindowWidth = vr::VRSettings()->GetInt32(k_pch_hmd_Section, k_pch_hmd_WindowWidth_Int32);
		m_nWindowHeight = vr::VRSettings()->GetInt32(k_pch_hmd_Section, k_pch_hmd_WindowHeight_Int32);
		m_nRenderWidth = vr::VRSettings()->GetInt32(k_pch_hmd_Section, k_pch_hmd_RenderWidth_Int32);
		m_nRenderHeight = vr::VRSettings()->GetInt32(k_pch_hmd_Section, k_pch_hmd_RenderHeight_Int32);
		m_flSecondsFromVsyncToPhotons = vr::VRSettings()->GetFloat(k_pch_hmd_Section, k_pch_hmd_SecondsFromVsyncToPhotons_Float);
		m_flDisplayFrequency = vr::VRSettings()->GetFloat(k_pch_hmd_Section, k_pch_hmd_DisplayFrequency_Float);

		DriverLog("driver_null: Serial Number: %s\n", m_sSerialNumber.c_str());
		DriverLog("driver_null: Model Number: %s\n", m_sModelNumber.c_str());
		DriverLog("driver_null: Window: %d %d %d %d\n", m_nWindowX, m_nWindowY, m_nWindowWidth, m_nWindowHeight);
		DriverLog("driver_null: Render Target: %d %d\n", m_nRenderWidth, m_nRenderHeight);
		DriverLog("driver_null: Seconds from Vsync to Photons: %f\n", m_flSecondsFromVsyncToPhotons);
		DriverLog("driver_null: Display Frequency: %f\n", m_flDisplayFrequency);
		DriverLog("driver_null: IPD: %f\n", m_flIPD);
		DriverLog("hmd_sim : \nFait!\n");
	}

	virtual ~ChmdDeviceDriver()
	{
	}


	virtual EVRInitError Activate(vr::TrackedDeviceIndex_t unObjectId)
	{
		DriverLog("hmd_sim : \nActivation\n");
		m_unObjectId = unObjectId;
		m_ulPropertyContainer = vr::VRProperties()->TrackedDeviceToPropertyContainer(m_unObjectId);


		vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, Prop_ModelNumber_String, m_sModelNumber.c_str());
		vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, Prop_RenderModelName_String, m_sModelNumber.c_str());
		vr::VRProperties()->SetFloatProperty(m_ulPropertyContainer, Prop_UserIpdMeters_Float, m_flIPD);
		vr::VRProperties()->SetFloatProperty(m_ulPropertyContainer, Prop_UserHeadToEyeDepthMeters_Float, 0.f);
		vr::VRProperties()->SetFloatProperty(m_ulPropertyContainer, Prop_DisplayFrequency_Float, m_flDisplayFrequency);
		vr::VRProperties()->SetFloatProperty(m_ulPropertyContainer, Prop_SecondsFromVsyncToPhotons_Float, m_flSecondsFromVsyncToPhotons);

		// return a constant that's not 0 (invalid) or 1 (reserved for Oculus)
		vr::VRProperties()->SetUint64Property(m_ulPropertyContainer, Prop_CurrentUniverseId_Uint64, 2);

		// avoid "not fullscreen" warnings from vrmonitor
		vr::VRProperties()->SetBoolProperty(m_ulPropertyContainer, Prop_IsOnDesktop_Bool, false);

		bool bSetupIconUsingExternalResourceFile = true;
		if (!bSetupIconUsingExternalResourceFile)
		{
			// Setup properties directly in code.
			// Path values are of the form {drivername}\icons\some_icon_filename.png
			vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_NamedIconPathDeviceOff_String, "{hmd_sim}/icons/headset_hmd_status_off.png");
			vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_NamedIconPathDeviceSearching_String, "{hmd_sim}/icons/headset_hmd_status_searching.gif");
			vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_NamedIconPathDeviceSearchingAlert_String, "{hmd_sim}/icons/headset_hmd_status_searching_alert.gif");
			vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_NamedIconPathDeviceReady_String, "{hmd_sim}/icons/headset_hmd_status_ready.png");
			vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_NamedIconPathDeviceReadyAlert_String, "{hmd_sim}/icons/headset_hmd_status_ready_alert.png");
			vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_NamedIconPathDeviceNotReady_String, "{hmd_sim}/icons/headset_hmd_status_error.png");
			vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_NamedIconPathDeviceStandby_String, "{hmd_sim}/icons/headset_hmd_status_standby.png");
			vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_NamedIconPathDeviceAlertLow_String, "{hmd_sim}/icons/headset_hmd_status_ready_low.png");
		}
		DriverLog("hmd_sim : \nActivation HMD finie!\n");
		return VRInitError_None;
	}

	virtual void Deactivate()
	{
		DriverLog("hmd_sim : \nDésactivé!\n");
		m_unObjectId = vr::k_unTrackedDeviceIndexInvalid;
	}

	virtual void EnterStandby()
	{
	}

	void* GetComponent(const char* pchComponentNameAndVersion)
	{
		DriverLog("hmd_sim : \nGetComponent\n");
		if (!_stricmp(pchComponentNameAndVersion, vr::IVRDisplayComponent_Version))
		{
			return (vr::IVRDisplayComponent*)this;
		}

		// override this to add a component to a driver
		return NULL;
	}

	virtual void PowerOff()
	{
	}

	/** debug request from a client */
	virtual void DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize)
	{
		if (unResponseBufferSize >= 1)
			pchResponseBuffer[0] = 0;
	}

	virtual void GetWindowBounds(int32_t* pnX, int32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight)
	{
		*pnX = m_nWindowX;
		*pnY = m_nWindowY;
		*pnWidth = m_nWindowWidth;
		*pnHeight = m_nWindowHeight;
	}

	virtual bool IsDisplayOnDesktop()
	{
		return true;
	}

	virtual bool IsDisplayRealDisplay()
	{
		return false;
	}

	virtual void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight)
	{
		*pnWidth = m_nRenderWidth;
		*pnHeight = m_nRenderHeight;
	}

	virtual void GetEyeOutputViewport(EVREye eEye, uint32_t* pnX, uint32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight)
	{
		*pnY = 0;
		*pnWidth = m_nWindowWidth / 2;
		*pnHeight = m_nWindowHeight;

		if (eEye == Eye_Left)
		{
			*pnX = 0;
		}
		else
		{
			*pnX = m_nWindowWidth / 2;
		}
	}

	virtual void GetProjectionRaw(EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom)
	{
		*pfLeft = -1.0;
		*pfRight = 1.0;
		*pfTop = -1.0;
		*pfBottom = 1.0;
	}

	virtual DistortionCoordinates_t ComputeDistortion(EVREye eEye, float fU, float fV)
	{
		DistortionCoordinates_t coordinates;
		coordinates.rfBlue[0] = fU;
		coordinates.rfBlue[1] = fV;
		coordinates.rfGreen[0] = fU;
		coordinates.rfGreen[1] = fV;
		coordinates.rfRed[0] = fU;
		coordinates.rfRed[1] = fV;
		return coordinates;
	}

	virtual void GetKeypresses() {
		if ((0x8000 & GetAsyncKeyState(VK_LEFT)) != 0) {
			yaw += 0.01;
		}
		if ((0x8000 & GetAsyncKeyState(VK_UP)) != 0) {
			pitch += 0.01;
		}
		if ((0x8000 & GetAsyncKeyState(VK_RIGHT)) != 0) {
			yaw -= 0.01;
		}
		if ((0x8000 & GetAsyncKeyState(VK_DOWN)) != 0) {
			pitch -= 0.01;
		}
		if ((0x8000 & GetAsyncKeyState(70)) != 0) {
			X -= 0.01;
		}
		if ((0x8000 & GetAsyncKeyState(86)) != 0) {
			X += 0.01;
		}
		if ((0x8000 & GetAsyncKeyState(67)) != 0) {
			Y -= 0.01;
		}
		if ((0x8000 & GetAsyncKeyState(66)) != 0) {
			Y += 0.01;
		}
	}

	virtual DriverPose_t GetPose()//appelé à chaque frame | C'EST LE CASQUE
	{
		GetKeypresses();

		DriverPose_t pose = { 0 };
		pose.poseIsValid = true;
		pose.result = TrackingResult_Running_OK;
		pose.deviceIsConnected = true;
		pose.vecPosition[2] = X;
		pose.vecPosition[0] = Y;


		pose.qWorldFromDriverRotation = ToQuaternion(0, 0, 0);
		pose.qDriverFromHeadRotation = ToQuaternion(0, 0, 0);

		pose.qRotation = ToQuaternion(0, yaw, pitch);

		return pose;
	}


	void RunFrame()	//Aussi appellé à chaque frame
	{
		// In a real driver, this should happen from some pose tracking thread.
		// The RunFrame interval is unspecified and can be very irregular if some other
		// driver blocks it for some periodic task.
		if (m_unObjectId != vr::k_unTrackedDeviceIndexInvalid)
		{
			vr::VRServerDriverHost()->TrackedDevicePoseUpdated(m_unObjectId, GetPose(), sizeof(DriverPose_t));
		}
	}

	std::string GetSerialNumber() const { return m_sSerialNumber; }

private:
	vr::TrackedDeviceIndex_t m_unObjectId;
	vr::PropertyContainerHandle_t m_ulPropertyContainer;

	std::string m_sSerialNumber = "CTRL_HMD_2008";
	std::string m_sModelNumber = "PhantomHMD";

	int32_t m_nWindowX;
	int32_t m_nWindowY;
	int32_t m_nWindowWidth;
	int32_t m_nWindowHeight;
	int32_t m_nRenderWidth;
	int32_t m_nRenderHeight;
	float m_flSecondsFromVsyncToPhotons;
	float m_flDisplayFrequency;
	float m_flIPD;
};


//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
class CServerhmd_sim : public IServerTrackedDeviceProvider
{
public:
	virtual EVRInitError Init(vr::IVRDriverContext* pDriverContext);
	virtual void Cleanup();
	virtual const char* const* GetInterfaceVersions() { return vr::k_InterfaceVersions; }
	virtual void RunFrame();
	virtual bool ShouldBlockStandbyMode() { return false; }
	virtual void EnterStandby() {}
	virtual void LeaveStandby() {}

private:
	ChmdDeviceDriver* m_pNullHmdLatest = nullptr;
};

CServerhmd_sim g_serverDriverNull;


EVRInitError CServerhmd_sim::Init(vr::IVRDriverContext* pDriverContext)
{
	VR_INIT_SERVER_DRIVER_CONTEXT(pDriverContext);
	InitDriverLog(vr::VRDriverLog());

	m_pNullHmdLatest = new ChmdDeviceDriver();
	vr::VRServerDriverHost()->TrackedDeviceAdded(m_pNullHmdLatest->GetSerialNumber().c_str(), vr::TrackedDeviceClass_HMD, m_pNullHmdLatest);

	return VRInitError_None;
}

void CServerhmd_sim::Cleanup()
{
	CleanupDriverLog();
	delete m_pNullHmdLatest;
	m_pNullHmdLatest = NULL;
}


void CServerhmd_sim::RunFrame()
{
	if (m_pNullHmdLatest)
	{
		m_pNullHmdLatest->RunFrame();
	}

	vr::VREvent_t vrEvent;
	while (vr::VRServerDriverHost()->PollNextEvent(&vrEvent, sizeof(vrEvent)))
	{
	}
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
HMD_DLL_EXPORT void* HmdDriverFactory(const char* pInterfaceName, int* pReturnCode)
{
	if (0 == strcmp(IServerTrackedDeviceProvider_Version, pInterfaceName))
	{
		return &g_serverDriverNull;
	}
	if (0 == strcmp(IVRWatchdogProvider_Version, pInterfaceName))
	{
		return &g_watchdogDriverNull;
	}

	if (pReturnCode)
		*pReturnCode = VRInitError_Init_InterfaceNotFound;

	return NULL;
}
