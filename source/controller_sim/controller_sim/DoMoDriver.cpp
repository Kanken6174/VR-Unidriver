#include "driverlog.h"
#include "controller_sim.h"

using namespace vr;

	DoMoDriver::DoMoDriver(int arraySize) {
		components = (VRcomponent*)malloc(sizeof(VRcomponent) * arraySize);
		if (components == nullptr)
			DriverLog("DoMoDriver: Malloc error\n");
		DriverLog("Started building DoMoDriver with arguments\n");
		deviceID = vr::k_unTrackedDeviceIndexInvalid;	//vaut 0xFFFFFFFF
		deviceContainer = vr::k_ulInvalidPropertyContainer;	//mise à valeur par défaut, seront changées

		int i = arraySize;
		inputPathDictionnary[i] = "/input/system/click";	//pour l'instant on a que le clic de menu, pour tester
		componentType[i] = 2;	//digital

		DictionnaryIndex = i;
	}

	DoMoDriver::DoMoDriver() {
		components = (VRcomponent*)malloc(sizeof(VRcomponent)*10);
		if (components == nullptr)
			DriverLog("DoMoDriver: Malloc error\n");
		DriverLog("Started building DoMoDriver without arguments\n");
		deviceID = vr::k_unTrackedDeviceIndexInvalid;	//vaut 0xFFFFFFFF
		deviceContainer = vr::k_ulInvalidPropertyContainer;	//mise à valeur par défaut, seront changées

		int i = 1;
		inputPathDictionnary[i] = "/input/system/click";	//pour l'instant on a que le clic de menu, pour tester
		componentType[i] = 2;	//digital

		DictionnaryIndex = i;
	}

	DoMoDriver::~DoMoDriver() {
		DriverLog("DoMoDriver: hans is here with the flammenwerfer\n");
		//C'est le destructeur de la classe, vide pour le moment.
	}

	void DoMoDriver::setStrProperty(vr::ETrackedDeviceProperty SVRproperty, std::string value)
	{
		vr::VRProperties()->SetStringProperty(deviceContainer, SVRproperty, value.c_str());
	}
	void DoMoDriver::setInt32Property(vr::ETrackedDeviceProperty SVRproperty, int32_t value)
	{
		vr::VRProperties()->SetInt32Property(deviceContainer, SVRproperty, value);
	}
	void DoMoDriver::setUInt64Property(vr::ETrackedDeviceProperty SVRproperty, uint64_t value)
	{
		vr::VRProperties()->SetUint64Property(deviceContainer, SVRproperty, value);
	}
	void DoMoDriver::setBoolProperty(vr::ETrackedDeviceProperty SVRproperty, bool value)
	{
		vr::VRProperties()->SetBoolProperty(deviceContainer, SVRproperty, value);
	}

	EVRInitError DoMoDriver::Activate(vr::TrackedDeviceIndex_t unObjectId)
	{
		DriverLog("Activate method called...\n");
		DoMoDriver::deviceID = unObjectId;	//on assigne l'id de cet appareil à partir de celui donné par le système OVR
		DriverLog(("DoMoCap has been assigned the DeviceIndex: "+std::to_string((uint32_t)unObjectId)+"\n").c_str()); // je sais, c'est horrible
		DoMoDriver::deviceContainer = vr::VRProperties()->TrackedDeviceToPropertyContainer(deviceID);	//on récupère le handle de notre appareil
		DriverLog(("DoMoCap has been assigned the propertyContainer: " + std::to_string((uint64_t)deviceID) + "\n").c_str());
		DoMoDriver::components = new VRcomponent(inputPathDictionnary[0], deviceContainer, DIGITAL);
		std::string pathProfile = "{controller_sim}/input/DoMoDriver_profile.json";
		setStrProperty(Prop_ModelNumber_String, DeviceRender);							//numéro de série de l'appareil
		setStrProperty(Prop_RenderModelName_String, DeviceRender);						//chemin modèle 3D à render
		setStrProperty(Prop_InputProfilePath_String, pathProfile);						//chemin vers profils d'input
		setUInt64Property(Prop_CurrentUniverseId_Uint64, 2);							//on doit en donner un différent de 0 (invalide) ou 1 (oculus)
		setBoolProperty(Prop_NeverTracked_Bool, false);									//Sera tracké, on met à false

		setInt32Property(Prop_ControllerRoleHint_Int32, TrackedControllerRole_RightHand);	//on se fait passer pour la main droite

		DriverLog(("Prop_ModelNumber_String : "+DeviceRender+"\n").c_str());
		DriverLog(("Prop_RenderModelName_String : " + DeviceRender + "\n").c_str());
		DriverLog(("Prop_ModelNumber_String : " + pathProfile + "\n").c_str());
		DriverLog((std::string("Prop_CurrentUniverseId_Uint64 : 2\n")).c_str());
		DriverLog((std::string("Prop_NeverTracked_Bool : false\n")).c_str());

		return EVRInitError::VRInitError_None;
	}

	void DoMoDriver::Deactivate(){deviceID = vr::k_unTrackedDeviceIndexInvalid;}

	void DoMoDriver::EnterStandby() {/*on pourrait stopped la collecte d'entrées du gant ici*/}

	void* DoMoDriver::GetComponent(const char* pchComponentNameAndVersion)
	{
		// override this to add a component to a driver
		return NULL;
	}

	void DoMoDriver::PowerOff(){}

	void DoMoDriver::DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize)
	{
		if (unResponseBufferSize >= 1)
			pchResponseBuffer[0] = 0;
		DriverLog("No\n");
	}
	/*Cette fonction gère la position (rotation quaternionique et position par vecteur) de l'objet,
	* qrotation est responsable de l'angle et Vecposition[3] de la position.
	*/
	void DoMoDriver::GetKeypresses() {
		if ((0x8000 & GetAsyncKeyState(VK_LEFT)) != 0) {
			if (yaw > 360 || yaw < 0)
				yaw = 0;
			else
				yaw += 0.01;
		}
		if ((0x8000 & GetAsyncKeyState(VK_UP)) != 0) {
			if (pitch > 360 || pitch < 0)
				pitch = 0;
			else
				pitch += 0.01;
		}
		if ((0x8000 & GetAsyncKeyState(VK_RIGHT)) != 0) {
			if (yaw > 360 || yaw < 0)
				yaw = 360;
			else
				yaw -= 0.01;
		}
		if ((0x8000 & GetAsyncKeyState(VK_DOWN)) != 0) {
			if (pitch > 360 || pitch < 0)
				pitch = 360;
			else
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

	DriverPose_t DoMoDriver::GetPose()
	{
		GetKeypresses();
		DriverPose_t pose = { 0 };
		double vectortr[2] = { 0 };
		pose.poseIsValid = true;
		pose.result = TrackingResult_Running_OK;
		pose.deviceIsConnected = true;

		pose.qWorldFromDriverRotation = ToQuaternion(0, 0, 0);
		pose.qDriverFromHeadRotation = ToQuaternion(0, 0, 0);
		pose.vecDriverFromHeadTranslation[2] = 0.5;

		pose.qRotation = ToQuaternion(0, yaw, pitch);
		pose.vecPosition[2] = X;
		pose.vecPosition[0] = Y;
		return pose;
	}
	/**
	*Cette fonction gère la mise à jour des valeurs d'entrée à chaque frame du jeu
	*/
	void DoMoDriver::RunFrame()
	{
		//DriverLog((std::string("Running frame : ") + std::to_string((uint32_t)deviceID) + "\n").c_str());
		if (deviceID != vr::k_unTrackedDeviceIndexInvalid)
		{
			vr::VRServerDriverHost()->TrackedDevicePoseUpdated(deviceID, GetPose(), sizeof(DriverPose_t));
			//DriverLog((std::string("Updating position: ") + std::to_string(X) +" "+std::to_string(Y)).c_str());
		}
		//DoMoDriver::components[0].UpdateSelf((0x8000 & GetAsyncKeyState('N')) != 0);
		
		int i = 0;
		for (int i = 0; i < DictionnaryIndex; i++)
		{
			DoMoDriver::components[i].UpdateSelf((0x8000 & GetAsyncKeyState('N')) != 0);
		}
		
	}

	std::string DoMoDriver::GetSerialNumber() {
		return m_sSerialNumber;
	}