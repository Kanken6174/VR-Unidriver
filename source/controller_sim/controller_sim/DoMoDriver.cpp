#include "driverlog.h"
#include "controller_sim.h"

#define ABSOLUTE vr::VRScalarType_Absolute	//input qui n'est pas relative, donc pas une souris ou trackball, plus joystick

#define TRIGGER vr::VRScalarUnits_NormalizedOneSided	//0 à 1
#define JOYSTICK vr::VRScalarUnits_NormalizedTwoSided	// -1 à 1
#define makeDigital CreateBooleanComponent
#define makeAnalog CreateScalarComponent
#define makeHaptic CreateHapticComponent
#define updateAn UpdateScalarComponent
#define updateBool UpdateBooleanComponent
#define updatehapt UpdatehapticComponent

using namespace vr;

	DoMoDriver::DoMoDriver() {
		DriverLog("DoMoDriver: Construction du DoMoDriver débutée\n");
		deviceID = vr::k_unTrackedDeviceIndexInvalid;	//vaut 0xFFFFFFFF
		deviceContainer = vr::k_ulInvalidPropertyContainer;	//mise à valeur par défaut, seront changées

		int i = 0;
		inputPathDictionnary[i] = "/input/system/click";	//digital
		inputPathDictionnary[i++] = "/input/a/click";		//digital
		inputPathDictionnary[i++] = "/input/b/click";		//digital
		inputPathDictionnary[i++] = "/input/trackpad/x";	//analog
		inputPathDictionnary[i++] = "/input/trackpad/y";	//analog
		inputPathDictionnary[i++] = "/input/trackpad/touch";//digital
		inputPathDictionnary[i++] = "/input/trigger/click";	//digital
		inputPathDictionnary[i++] = "/input/trigger/value";	//analog
		inputPathDictionnary[i++] = "/input/thumbstick/x";	//analog
		inputPathDictionnary[i++] = "/input/thumbstick/y";	//analog
		inputPathDictionnary[i++] = "/output/haptic";	//haptic
		DictionnaryIndex = i;
	}

	DoMoDriver::~DoMoDriver() {
		DriverLog("DoMoDriver: hans is here with the flammenwerfer\n");
		//C'est le destructeur de la classe, vide pour le moment.
	}

	EVRInitError DoMoDriver::Activate(vr::TrackedDeviceIndex_t unObjectId)
	{
		deviceID = unObjectId;	//on assigne l'id de cet appareil à partir de celui donné par le système OVR
		deviceContainer = vr::VRProperties()->TrackedDeviceToPropertyContainer(deviceID);

		vr::VRProperties()->SetStringProperty(deviceContainer, Prop_ModelNumber_String, NombreDeModele.c_str());
		vr::VRProperties()->SetStringProperty(deviceContainer, Prop_RenderModelName_String, NombreDeModele.c_str());
		vr:VRProperties()->SetUint64Property(deviceContainer, Prop_CurrentUniverseId_Uint64, 3);	//on doit en donner un différent de 0 (invalide) ou 1 (oculus)
		//valeurs liées au tracking
		vr::VRProperties()->SetBoolProperty(deviceContainer, Prop_IsOnDesktop_Bool, false);	//Ignore les warnings liés à l'écran
		vr::VRProperties()->SetBoolProperty(deviceContainer, Prop_NeverTracked_Bool, true); //Pas encore tracké donc on valide ça
		vr::VRProperties()->SetInt32Property(deviceContainer, Prop_ControllerRoleHint_Int32, TrackedControllerRole_RightHand);	//on se fait passer pour la main droite
		//chemin vers les profils d'input
		vr::VRProperties()->SetStringProperty(deviceContainer, Prop_InputProfilePath_String, ("{DoMoCap}/input/mycontroller_profile.json"));
		
		/**
		* Création des composants d'input, cela se fait avec une méthode de la forme suivante:
		* vr::VRDriverInput()->CreateBooleanComponent( Container de l'appareil, Chemin d'action SVR, handle de ce composant (retour pointeur) );
		*/
		int d = 0;
		int i = 0;
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
		Quaternion rotationQuat;
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
		//vr::VRDriverInput()->UpdateBooleanComponent(m_compA, (0x8000 & GetAsyncKeyState('A')) != 0, 0);
	}

	std::string DoMoDriver::GetSerialNumber() {
		return m_sSerialNumber;
	}