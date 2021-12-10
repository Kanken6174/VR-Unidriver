#include "driverlog.h"
#include "controller_sim.h"

using namespace vr;

	DoMoDriver::DoMoDriver() {
		DriverLog("Started building DoMoDriver without arguments\n");

		inputPathDictionnary.push_back("/input/a/click");
		inputPathDictionnary.push_back("/input/b/click");
		inputPathDictionnary.push_back("/input/c/click");

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

		for (std::string inputPath : DoMoDriver::inputPathDictionnary) {
			VRcomponent* addme = new VRcomponent(inputPath, deviceContainer, DIGITAL);
			DoMoDriver::components.push_back(addme);
			DriverLog("Added DIGITAL component to device");
		}


		DriverLog((std::string("Post-activation, registering components...")).c_str());

		for (VRcomponent* component : DoMoDriver::components)	//foreach
			component->registerSelf();

		return EVRInitError::VRInitError_None;
	}

	void DoMoDriver::registerProperties(vr::TrackedDeviceIndex_t unObjectId) {
		std::string pathProfile = "{controller_sim}/input/DoMoDriver_profile.json";
		setStrProperty(Prop_ModelNumber_String, DeviceRender);							//numéro de série de l'appareil
		setStrProperty(Prop_RenderModelName_String, DeviceRender);						//chemin modèle 3D à render
		setStrProperty(Prop_InputProfilePath_String, pathProfile);						//chemin vers profils d'input
		setUInt64Property(Prop_CurrentUniverseId_Uint64, 2);							//on doit en donner un différent de 0 (invalide) ou 1 (oculus)
		setBoolProperty(Prop_NeverTracked_Bool, false);									//Sera tracké, on met à false

		setInt32Property(Prop_ControllerRoleHint_Int32, TrackedControllerRole_RightHand);	//on se fait passer pour la main droite

		DriverLog(("Prop_ModelNumber_String : " + DeviceRender + "\n").c_str());
		DriverLog(("Prop_RenderModelName_String : " + DeviceRender + "\n").c_str());
		DriverLog(("Prop_ModelNumber_String : " + pathProfile + "\n").c_str());
		DriverLog((std::string("Prop_CurrentUniverseId_Uint64 : 2\n")).c_str());
		DriverLog((std::string("Prop_NeverTracked_Bool : false\n")).c_str());
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
		if ((0x8000 & GetAsyncKeyState(VK_NUMPAD1)) != 0) {
			if (yaw > 360 || yaw < 0)
				yaw = 0;
			else
				yaw += 0.01;
		}
		if ((0x8000 & GetAsyncKeyState(VK_NUMPAD5)) != 0) {
			if (pitch > 360 || pitch < 0)
				pitch = 0;
			else
				pitch += 0.01;
		}
		if ((0x8000 & GetAsyncKeyState(VK_NUMPAD3)) != 0) {
			if (yaw > 360 || yaw < 0)
				yaw = 360;
			else
				yaw -= 0.01;
		}
		if ((0x8000 & GetAsyncKeyState(VK_NUMPAD2)) != 0) {
			if (pitch > 360 || pitch < 0)
				pitch = 360;
			else
				pitch -= 0.01;
		}
		/*if ((0x8000 & GetAsyncKeyState(70)) != 0) {	//F
			
			X -= 0.01;
		}
		if ((0x8000 & GetAsyncKeyState(86)) != 0) {	//B
			X += 0.01;
		}
		if ((0x8000 & GetAsyncKeyState(67)) != 0) { //C
			Y -= 0.01;
		}
		if ((0x8000 & GetAsyncKeyState(66)) != 0) {	//V
			Y += 0.01;
		}*/
	}

	DriverPose_t DoMoDriver::GetPose()
	{
		GetKeypresses();	//on le laisse statique dans l'espace pour l'instant
		DriverPose_t pose = { 0 };
		pose.poseIsValid = true;
		pose.result = TrackingResult_Running_OK;
		pose.deviceIsConnected = true;

		pose.qWorldFromDriverRotation = ToQuaternion(0, 0, 0);
		pose.qDriverFromHeadRotation = ToQuaternion(0, 0, 0);
		pose.vecDriverFromHeadTranslation[2] = -0.5;	//on met la manette juste devant la caméra par défaut (la caméra est en -1, car l'axe X est inversé)
		pose.vecDriverFromHeadTranslation[1] = -0.25;
		pose.vecDriverFromHeadTranslation[0] = 0.25;

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
		if (DoMoDriver::deviceID != vr::k_unTrackedDeviceIndexInvalid)
		{
			vr::VRServerDriverHost()->TrackedDevicePoseUpdated(DoMoDriver::deviceID, GetPose(), sizeof(DriverPose_t));
		}
		if (components.size() <= 0) { DriverLog("Error, empty component vector..."); return; }
		//for (int i = 0; i < DictionnaryIndex; i++)
		//{
			DoMoDriver::components[0]->UpdateSelf((0x8000 & GetAsyncKeyState(78)) != 0);	//N
			DoMoDriver::components[1]->UpdateSelf((0x8000 & GetAsyncKeyState(72)) != 0);	//H
			DoMoDriver::components[2]->UpdateSelf((0x8000 & GetAsyncKeyState(74)) != 0);	//J
		//}
		
	}

	std::string DoMoDriver::GetSerialNumber() {
		return m_sSerialNumber;
	}