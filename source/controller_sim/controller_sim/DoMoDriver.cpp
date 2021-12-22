/**
* @author Yorick Geoffre
* @brief defines a single device, which can be host to multiple component and has a pose (rotation + position) in 3d space
* @version 0.5
* @date 16/12/2021
*/

#include "controller_sim.h"

using namespace vr;

	DoMoDriver::DoMoDriver(DriverDataTemplate ddt) {
		DriverLog("Started building %s by DriverDataTemplate", ddt.name.c_str());
		ObsoleteMode = false;
		localData = ddt;
		m_sSerialNumber = ddt.name;
		DeviceRender = ddt.renderModel;

		DriverLog("Done");
	}

	DoMoDriver::DoMoDriver(std::string name) {
		DriverLog("Started building DoMoDriver by name, stub_mode enabled\n");
		m_sSerialNumber = name;

		inputPathDictionnary.push_back("/input/a/click");
		inputPathDictionnary.push_back("/input/b/click");
		inputPathDictionnary.push_back("/input/system/click");
		//en mode stub, le type d'entrée est supérieur à 5, le composant se met donc en mode stub et observe la touche de clavier correspondante.
		//ce mode ne nécessite aucun argument en update()
		componentType.push_back(78); //N key
		componentType.push_back(72); //H key
		componentType.push_back(74); //J key

		DriverLog("Created 3 keyboard-based stub components\n");
	}

	DoMoDriver::DoMoDriver(std::string name, std::vector<int> compoTypes, std::vector<std::string> compoPaths) {
		DriverLog("Started building DoMoDriver with all arguments\n");

		m_sSerialNumber = name;
		inputPathDictionnary = compoPaths;
		componentType = compoTypes;
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
		if (ObsoleteMode) {
			ObsoleteActivation(unObjectId);
		}
		else {
			ModernActivation(unObjectId);
		}
		DriverLog("________________________Registering components_______________");
		for (VRcomponent* component : DoMoDriver::components) {	//foreach
			EVRInputError ER = component->registerSelf();
			DriverLog("Component registered with return code %d",ER);
		}

		return EVRInitError::VRInitError_None;
	}

	EVRInitError DoMoDriver::ModernActivation(vr::TrackedDeviceIndex_t unObjectId) {
		DriverLog("Modern activate method called...");
		deviceID = unObjectId;
		DriverLog("%s has been assigned the DeviceIndex: %d",localData.name.c_str(), unObjectId);
		deviceContainer = vr::VRProperties()->TrackedDeviceToPropertyContainer(deviceID);

		registerProperties(unObjectId);

		for (ComponentDataTemplate* componentData : localData.components) {
			VRcomponent* newcomponent = new VRcomponent(deviceContainer,(*componentData));
			DoMoDriver::components.push_back(newcomponent);
		}

		return EVRInitError::VRInitError_None;
	}

	EVRInitError DoMoDriver::ObsoleteActivation(vr::TrackedDeviceIndex_t unObjectId) {
		DriverLog("Obsolete activate method called...\n");
		DoMoDriver::deviceID = unObjectId;	//on assigne l'id de cet appareil à partir de celui donné par le système OVR
		DriverLog(("DoMoCap has been assigned the DeviceIndex: " + std::to_string((uint32_t)unObjectId) + "\n").c_str()); // je sais, c'est horrible
		DoMoDriver::deviceContainer = vr::VRProperties()->TrackedDeviceToPropertyContainer(deviceID);	//on récupère le handle de notre appareil
		DriverLog(("DoMoCap has been assigned the propertyContainer: " + std::to_string((uint64_t)deviceID) + "\n").c_str());

		if (inputPathDictionnary.size() == componentType.size()) {
			for (int i = 0; i != inputPathDictionnary.size(); i++) {	//std::string inputPath : DoMoDriver::inputPathDictionnary
				VRcomponent* addme = new VRcomponent(inputPathDictionnary[i], deviceContainer, componentType[i]);
				DoMoDriver::components.push_back(addme);
				DriverLog("Added DIGITAL component to device");
			}
		}
		else {
			DriverLog("Error, input path and component type vector sizes mismatched, skipping component creation...");
			return EVRInitError::VRInitError_Init_MismatchedRuntimes;
		}


		DriverLog((std::string("Post-activation, registering components...")).c_str());
		return EVRInitError::VRInitError_None;
	}

	void DoMoDriver::registerProperties(vr::TrackedDeviceIndex_t unObjectId) {
		setStrProperty(Prop_InputProfilePath_String, "{controller_sim}/input/" + m_sSerialNumber + "_profile.json");
		setStrProperty(Prop_ModelNumber_String, m_sSerialNumber);							//numéro de série de l'appareil
		setStrProperty(Prop_RenderModelName_String, DeviceRender);						//chemin modèle 3D à render
		setUInt64Property(Prop_CurrentUniverseId_Uint64, 2);							//on doit en donner un différent de 0 (invalide) ou 1 (oculus)
		setBoolProperty(Prop_NeverTracked_Bool, false);									//Sera tracké, on met à false
		setInt32Property(Prop_ControllerRoleHint_Int32, TrackedControllerRole_RightHand);	//on se fait passer pour la main droite

		DriverLog("______________________Registering device properties_____________________");
		DriverLog(("Prop_ModelNumber_String : " + DeviceRender + "\n").c_str());
		DriverLog(("Prop_RenderModelName_String : " + DeviceRender + "\n").c_str());
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

	DriverPose_t DoMoDriver::GetPoseStubmode()
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

	DriverPose_t DoMoDriver::GetPoseProvided(HmdQuaternion_t poseRotation, vector<double> posePosition) {
		DriverPose_t pose = { 0 };
		pose.poseIsValid = true;
		pose.result = TrackingResult_Running_OK;



		return pose;
	}

	DriverPose_t DoMoDriver::GetPose() {
		DriverPose_t err = DriverPose_t();
		return err;
	}

	/**
	*Cette fonction gère la mise à jour des valeurs d'entrée à chaque frame du jeu
	*/
	void DoMoDriver::RunFrameStub()
	{
		if (DoMoDriver::deviceID != vr::k_unTrackedDeviceIndexInvalid)
		{
			vr::VRServerDriverHost()->TrackedDevicePoseUpdated(DoMoDriver::deviceID, GetPoseStubmode(), sizeof(DriverPose_t));
		}
		else {
			DriverLog("Invalid DeviceID, skipping pose update...");
		}
		if (components.size() <= 0) { DriverLog("No components on device, skipping..."); return; }
		
		for (VRcomponent* component : DoMoDriver::components)
			component->UpdateSelf();
	}

	void DoMoDriver::RunFrameProvided(HmdQuaternion_t poseRotation, vector<double> posePosition, vector<string> Componentdata) {
		if (DoMoDriver::deviceID != vr::k_unTrackedDeviceIndexInvalid)
		{
			vr::VRServerDriverHost()->TrackedDevicePoseUpdated(DoMoDriver::deviceID, GetPoseStubmode(), sizeof(DriverPose_t));
		}
		else {
			DriverLog("Invalid DeviceID, skipping pose update...");
		}
		if (components.size() <= 0) { DriverLog("No components on device, skipping..."); return; }

		else {
			std::string responsabilityChain = "";
			for (VRcomponent* component : DoMoDriver::components)
				if (!(component->UpdateSelf(&responsabilityChain))) {	//on a un pattern de chaîne de repsonsabilité ici, chanque composant prend sa part de string
					DriverLog("An error has occured in the responsability chain of the components, string may be missing parts.");
					return;	//si une erreur a eu lieu (typique: le string n'a plus de ressources disponibles), on renvoie à steamvr sans planter.
				}
		}
	}

	std::string DoMoDriver::GetSerialNumber() {
		return m_sSerialNumber;
	}