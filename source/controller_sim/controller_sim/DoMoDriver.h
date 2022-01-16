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


/*Cette classe repr�sente un appareil track� (impl�mente ITrackedDeviceServerDriver), il a une position et une rotation,
* et peut
*/
class DoMoDriver : public vr::ITrackedDeviceServerDriver
{
private:
	vr::TrackedDeviceIndex_t deviceID = vr::k_unTrackedDeviceIndexInvalid;	//m_unObjectId dans la doc
	vr::PropertyContainerHandle_t deviceContainer = vr::k_ulInvalidPropertyContainer;	//m_ulpropertyContainer dans la doc

	std::string m_sSerialNumber = "DoMoDriver";	//le nom de l'appareil
	std::string DeviceRender = "oculus_cv1_controller_right";	//� la fois le "mod�le" de l'appareil, mais aussi son mod�le 3d (rendermodels)

	DriverDataTemplate localData;	//version moderne

	std::vector <VRcomponent*> components;	//un vecteur de pointeurs vers des VRcomponent

	double	yaw = 0,	pitch = 0,	roll = 0,	//composants utilis�s par le stub uniquement (rotation)
			X = 0,		Y = 0,		Z = 0;		//composants utilis�s par les 2 versions (position)

	HmdQuaternion_t* DeviceRotation = new HmdQuaternion_t();	//composant de rotation de la version poseProvided()

	bool ObsoleteMode = false;	//d�finit la version de la m�thode d'activation � utiliser
	//Obsol�tes, sauf si utilisation du driver sans les dataTemplates
	std::vector <std::string> inputPathDictionnary;//un tableau de chemins SVR, type /input/machin/truc
	std::vector <int> componentType;

public:
	DoMoDriver(DriverDataTemplate ddt);
	DoMoDriver(std::string name);
	DoMoDriver(std::string name, std::vector<int> compoTypes, std::vector<std::string> compoPaths);

	virtual ~DoMoDriver();

	//Ces 4 fonctions servent juste � factoriser celles donn�es par openVR pour modifier des valeurs
	virtual void setStrProperty(vr::ETrackedDeviceProperty SVRproperty, std::string value);
	virtual void setInt32Property(vr::ETrackedDeviceProperty SVRproperty, int32_t value);
	virtual void setUInt64Property(vr::ETrackedDeviceProperty SVRproperty, uint64_t value);
	virtual void setBoolProperty(vr::ETrackedDeviceProperty SVRproperty, bool value);

	virtual EVRInitError ModernActivation(vr::TrackedDeviceIndex_t unObjectId);
	virtual EVRInitError ObsoleteActivation(vr::TrackedDeviceIndex_t unObjectId);	//d�sormais inutilis�

	virtual void registerProperties(vr::TrackedDeviceIndex_t unObjectId);

	//fonctions requises par l'interface ITrackedDeviceServerDriver, commes donn�es dans le sample
	virtual EVRInitError Activate(vr::TrackedDeviceIndex_t unObjectId);
	virtual void Deactivate();
	virtual void EnterStandby();
	virtual void* GetComponent(const char* pchComponentNameAndVersion);
	virtual void PowerOff();
	virtual void DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize);

	/*Cette fonction g�re la position (rotation quaternionique et position par vecteur) de l'objet,
	* qrotation est responsable de l'angle et Vecposition[3] de la position.
	*/
	virtual void GetKeypresses();	//version stub�ee (on r�cup�re les touches de clavier
	virtual DriverPose_t GetPoseStubmode();	//stubbed
	virtual DriverPose_t GetPoseProvided();	// "vraie" version
	virtual DriverPose_t GetPose();	//version forc�e par SteamVR et pas utilis�e (d�crite dans interfaceRequires.cpp)
	/**
	*Cette fonction g�re la mise � jour des valeurs d'entr�e � chaque frame du jeu
	*/
	virtual void RunFrameStub();
	virtual void RunFrameRaw(string raw);
	virtual std::string GetSerialNumber();
	/**
	* Cette fonction g�re la mise � jour de valeurs par celles re�ues du tunnel nomm�
	*/
	virtual vector<string> UpdateInternalValuesFromPipedData(string pipeData);
};