#pragma once
#include "VRComponent.h"
/**
* maths.h functions and definitions
* used mainly for mathematic angle conversions
*/
struct Quaternion
{
	double w, x, y, z;
};

vr::HmdQuaternion_t ToQuaternion(double yaw, double pitch, double roll);

/*
-------------------------------------------------------CLASSE DRIVER---------------------------------------------------
*/


/*Cette classe représente un appareil tracké (implémente ITrackedDeviceServerDriver), il a une position et une rotation,
* et peut
*/
class DoMoDriver : public vr::ITrackedDeviceServerDriver
{
private:
	vr::TrackedDeviceIndex_t deviceID = vr::k_unTrackedDeviceIndexInvalid;	//m_unObjectId dans la doc
	vr::PropertyContainerHandle_t deviceContainer = vr::k_ulInvalidPropertyContainer;	//m_ulpropertyContainer dans la doc

	std::string m_sSerialNumber = "DoMoDriver";	//le nom de l'appareil
	std::string DeviceRender = "oculus_cv1_controller_right";	//à la fois le "modèle" de l'appareil, mais aussi son modèle 3d (rendermodels)

	DriverDataTemplate localData;	//version moderne

	std::vector <VRcomponent*> components;	//un vecteur de pointeurs vers des VRcomponent

	double	yaw = 0,	pitch = 0,	roll = 0,	//composants utilisés par le stub uniquement (rotation)
			X = 0,		Y = 0,		Z = 0;		//composants utilisés par les 2 versions (position)

	HmdQuaternion_t* DeviceRotation = new HmdQuaternion_t();	//composant de rotation de la version poseProvided()

	bool ObsoleteMode = false;	//définit la version de la méthode d'activation à utiliser
	//Obsolètes, sauf si utilisation du driver sans les dataTemplates
	std::vector <std::string> inputPathDictionnary;//un tableau de chemins SVR, type /input/machin/truc
	std::vector <int> componentType;

public:
	DoMoDriver(DriverDataTemplate ddt);
	DoMoDriver(std::string name);
	DoMoDriver(std::string name, std::vector<int> compoTypes, std::vector<std::string> compoPaths);

	virtual ~DoMoDriver();

	//Ces 4 fonctions servent juste à factoriser celles données par openVR pour modifier des valeurs
	virtual void setStrProperty(vr::ETrackedDeviceProperty SVRproperty, std::string value);
	virtual void setInt32Property(vr::ETrackedDeviceProperty SVRproperty, int32_t value);
	virtual void setUInt64Property(vr::ETrackedDeviceProperty SVRproperty, uint64_t value);
	virtual void setBoolProperty(vr::ETrackedDeviceProperty SVRproperty, bool value);

	virtual EVRInitError ModernActivation(vr::TrackedDeviceIndex_t unObjectId);
	virtual EVRInitError ObsoleteActivation(vr::TrackedDeviceIndex_t unObjectId);	//désormais inutilisé

	virtual void registerProperties(vr::TrackedDeviceIndex_t unObjectId);

	//fonctions requises par l'interface ITrackedDeviceServerDriver, commes données dans le sample
	virtual EVRInitError Activate(vr::TrackedDeviceIndex_t unObjectId);
	virtual void Deactivate();
	virtual void EnterStandby();
	virtual void* GetComponent(const char* pchComponentNameAndVersion);
	virtual void PowerOff();
	virtual void DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize);

	/*Cette fonction gère la position (rotation quaternionique et position par vecteur) de l'objet,
	* qrotation est responsable de l'angle et Vecposition[3] de la position.
	*/
	virtual void GetKeypresses();	//version stubéee (on récupère les touches de clavier
	virtual DriverPose_t GetPoseStubmode();	//stubbed
	virtual DriverPose_t GetPoseProvided();	// "vraie" version
	virtual DriverPose_t GetPose();	//version forcée par SteamVR et pas utilisée (décrite dans interfaceRequires.cpp)
	/**
	*Cette fonction gère la mise à jour des valeurs d'entrée à chaque frame du jeu
	*/
	virtual void RunFrameStub();
	virtual void RunFrameRaw(string raw);
	virtual std::string GetSerialNumber();
	/**
	* Cette fonction gère la mise à jour de valeurs par celles reçues du tunnel nommé
	*/
	virtual vector<string> UpdateInternalValuesFromPipedData(string pipeData);
};