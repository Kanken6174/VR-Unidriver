#include "driverlog.h"
#include "controller_sim.h"

using namespace vr;

	DoMoDriver::DoMoDriver(int arraySize) {
		components = (VRcomponent*)malloc(sizeof(VRcomponent) * arraySize);
		if (components == nullptr)
			DriverLog("DoMoDriver: Malloc error\n");
		DriverLog("DoMoDriver: Construction du DoMoDriver débutée\n");
		deviceID = vr::k_unTrackedDeviceIndexInvalid;	//vaut 0xFFFFFFFF
		deviceContainer = vr::k_ulInvalidPropertyContainer;	//mise à valeur par défaut, seront changées

		int i = 0;
		inputPathDictionnary[i] = "/input/system/click";	//pour l'instant on a que le clic de menu, pour tester
		componentType[i] = 2;	//digital

		DictionnaryIndex = i;
	}

	DoMoDriver::DoMoDriver() {
		components = (VRcomponent*)malloc(sizeof(VRcomponent)*10);
		if (components == nullptr)
			DriverLog("DoMoDriver: Malloc error\n");
		DriverLog("DoMoDriver: Construction du DoMoDriver débutée\n");
		deviceID = vr::k_unTrackedDeviceIndexInvalid;	//vaut 0xFFFFFFFF
		deviceContainer = vr::k_ulInvalidPropertyContainer;	//mise à valeur par défaut, seront changées

		int i = 0;
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
		deviceID = unObjectId;	//on assigne l'id de cet appareil à partir de celui donné par le système OVR
		deviceContainer = vr::VRProperties()->TrackedDeviceToPropertyContainer(deviceID);	//on récupère le handle de notre appareil

		components = new VRcomponent(inputPathDictionnary[0], deviceContainer, DIGITAL);

		setStrProperty(Prop_ModelNumber_String, NombreDeModele);							//numéro de série de l'appareil
		setStrProperty(Prop_RenderModelName_String, NombreDeModele);						//chemin modèle 3D à render
		setStrProperty(Prop_InputProfilePath_String, "{DoMoCap}/input/mycontroller_profile.json");	//chemin vers profils d'input
		setUInt64Property(Prop_CurrentUniverseId_Uint64, 3);								//on doit en donner un différent de 0 (invalide) ou 1 (oculus)
		setBoolProperty(Prop_IsOnDesktop_Bool, false);										//Ignore les warnings liés à l'écran
		setBoolProperty(Prop_NeverTracked_Bool, true);										//Pas encore tracké donc on valide ça

		setInt32Property(Prop_ControllerRoleHint_Int32, TrackedControllerRole_RightHand);	//on se fait passer pour la main droite

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
	DriverPose_t DoMoDriver::GetPose()
	{
		double posVect[3] = { 0 };
		DriverPose_t pose = { 0 };
		pose.poseIsValid = false;
		pose.result = TrackingResult_Calibrating_OutOfRange;
		pose.deviceIsConnected = true;

		pose.qWorldFromDriverRotation = ToQuaternion(1, 0, 0);
		pose.qDriverFromHeadRotation = ToQuaternion(1, 0, 0);

		pose.qRotation = ToQuaternion(1, 0, 0);
		pose.vecPosition[0] = posVect[0];
		pose.vecPosition[1] = posVect[1];
		pose.vecPosition[2] = posVect[2];
		return pose;
	}
	/**
	*Cette fonction gère la mise à jour des valeurs d'entrée à chaque frame du jeu
	*/
	void DoMoDriver::RunFrame()
	{
		int i = 0;
		for(int i = 0; i < DictionnaryIndex; i++)
		{
			DoMoDriver::components[i].UpdateSelf((0x8000 & GetAsyncKeyState('N')) != 0);
		}
	}

	std::string DoMoDriver::GetSerialNumber() {
		return m_sSerialNumber;
	}