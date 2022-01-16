/**
* @author Yorick Geoffre
* @brief this file holds the declaration of the DoMoDriver object, which represents a single devices with its various components
* @version 0.1
* @date 16/12/2021
*/

#pragma once
#include "VRComponent.h"
#include "MathOps.h"


/// <summary>
/// Cette classe représente un appareil tracké (implémente ITrackedDeviceServerDriver), il a une position et une rotation, et peut
/// </summary>
class DoMoDriver : public vr::ITrackedDeviceServerDriver
{
private:
	vr::TrackedDeviceIndex_t deviceID = vr::k_unTrackedDeviceIndexInvalid;	//m_unObjectId dans la doc
	vr::PropertyContainerHandle_t deviceContainer = vr::k_ulInvalidPropertyContainer;	//m_ulpropertyContainer dans la doc

	std::string m_sSerialNumber = "DoMoDriver";	//le nom de l'appareil
	std::string DeviceRender = "oculus_cv1_controller_right";	//à la fois le "modèle" de l'appareil, mais aussi son modèle 3d (rendermodels)

	DriverDataTemplate localData;	//Représente la template à partir de laquelle ce driver a été créé. les templates sont chargées à partir du fichier de configuration .DMC

	std::vector <VRcomponent*> components;	//un vecteur de pointeurs vers des VRcomponent, contient les composants de cet appareil

	double	yaw = 0,	pitch = 0,	roll = 0,	//composants utilisés par le stub uniquement (rotation)
			X = 0,		Y = 0,		Z = 0;		//composants utilisés par les 2 versions (position)

	HmdQuaternion_t* DeviceRotation = new HmdQuaternion_t();	//composant de rotation de la version poseProvided() (non-stub)

	bool ObsoleteMode = false;	//définit la version de la méthode d'activation à utiliser, faux par défaut pour utiliser la version moderne

	//Obsolètes, sauf si utilisation du driver sans les dataTemplates
	std::vector <std::string> inputPathDictionnary;//un tableau de chemins SVR, type /input/machin/truc, obsolète
	std::vector <int> componentType;	//ancienne façon de créer les composants en précisant leur type pour chaque, obsolète

public:
	/// <summary>
	/// Le constructeur d'une classe DoMoDriver (version moderne, désactive le mode obsolète si il est appellé)
	/// </summary>
	/// <param name="driverDataTemplate">La data Template de ce driver, qui décrit l'appareil que ce driver représente</param>
	DoMoDriver(DriverDataTemplate driverDataTemplate);

	//constructeur Obsolète
	[[deprecated("Ancienne version qui n'utilise pas les DataTemplate, à éviter")]]
	DoMoDriver(std::string name);
	//Constructeur Obsolète
	[[deprecated("Ancienne version qui n'utilise pas les DataTemplate, à éviter")]]
	DoMoDriver(std::string name, std::vector<int> compoTypes, std::vector<std::string> compoPaths);

	/// <summary>
	/// Le destructeur de ce driver
	/// </summary>
	virtual ~DoMoDriver();

	//Ces 4 fonctions servent juste à factoriser celles données par openVR pour modifier des valeurs
	virtual void setStrProperty(vr::ETrackedDeviceProperty SVRproperty, std::string value);
	virtual void setInt32Property(vr::ETrackedDeviceProperty SVRproperty, int32_t value);
	virtual void setUInt64Property(vr::ETrackedDeviceProperty SVRproperty, uint64_t value);
	virtual void setBoolProperty(vr::ETrackedDeviceProperty SVRproperty, bool value);


	virtual EVRInitError ModernActivation(vr::TrackedDeviceIndex_t unObjectId);

	//Activation obsolète
	virtual EVRInitError [[deprecated("Ancienne version qui n'utilise pas les DataTemplate, à éviter")]] ObsoleteActivation(vr::TrackedDeviceIndex_t unObjectId);

	virtual void registerProperties(vr::TrackedDeviceIndex_t unObjectId);

	//fonctions requises par l'interface ITrackedDeviceServerDriver, commes données dans le sample, elles ne sont pas utilisées
	[[maybe_unused]] virtual EVRInitError Activate(vr::TrackedDeviceIndex_t unObjectId);
	[[maybe_unused]] virtual void Deactivate();
	[[maybe_unused]] virtual void EnterStandby();
	[[maybe_unused]] virtual void* GetComponent(const char* pchComponentNameAndVersion);
	[[maybe_unused]] virtual void PowerOff();
	[[maybe_unused]] virtual void DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize);

	/*Ces fonctions gèrent la position (rotation quaternionique et position par vecteur) de l'objet,
	* qrotation est responsable de l'angle et Vecposition[3] de la position.
	*/
	
	/// <summary>
	/// récupère les touches de clavier, utilisé par la versions stub de GetPose uniquement
	/// </summary>
	virtual void GetKeypresses();
	virtual DriverPose_t GetPoseStubmode();	//stubbed
	virtual DriverPose_t GetPoseProvided();	// "vraie" version

	[[maybe_unused]] virtual DriverPose_t GetPose();	//version forcée par SteamVR et pas utilisée (décrite dans interfaceRequires.cpp)
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