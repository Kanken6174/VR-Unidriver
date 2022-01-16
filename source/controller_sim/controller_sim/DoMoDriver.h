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
/// Cette classe repr�sente un appareil track� (impl�mente ITrackedDeviceServerDriver), il a une position et une rotation, et peut
/// </summary>
class DoMoDriver : public vr::ITrackedDeviceServerDriver
{
private:
	vr::TrackedDeviceIndex_t deviceID = vr::k_unTrackedDeviceIndexInvalid;	//m_unObjectId dans la doc
	vr::PropertyContainerHandle_t deviceContainer = vr::k_ulInvalidPropertyContainer;	//m_ulpropertyContainer dans la doc

	std::string m_sSerialNumber = "DoMoDriver";	//le nom de l'appareil
	std::string DeviceRender = "oculus_cv1_controller_right";	//� la fois le "mod�le" de l'appareil, mais aussi son mod�le 3d (rendermodels)

	DriverDataTemplate localData;	//Repr�sente la template � partir de laquelle ce driver a �t� cr��. les templates sont charg�es � partir du fichier de configuration .DMC

	std::vector <VRcomponent*> components;	//un vecteur de pointeurs vers des VRcomponent, contient les composants de cet appareil

	double	yaw = 0,	pitch = 0,	roll = 0,	//composants utilis�s par le stub uniquement (rotation)
			X = 0,		Y = 0,		Z = 0;		//composants utilis�s par les 2 versions (position)

	HmdQuaternion_t* DeviceRotation = new HmdQuaternion_t();	//composant de rotation de la version poseProvided() (non-stub)

	bool ObsoleteMode = false;	//d�finit la version de la m�thode d'activation � utiliser, faux par d�faut pour utiliser la version moderne

	//Obsol�tes, sauf si utilisation du driver sans les dataTemplates
	std::vector <std::string> inputPathDictionnary;//un tableau de chemins SVR, type /input/machin/truc, obsol�te
	std::vector <int> componentType;	//ancienne fa�on de cr�er les composants en pr�cisant leur type pour chaque, obsol�te

public:
	/// <summary>
	/// Le constructeur d'une classe DoMoDriver (version moderne, d�sactive le mode obsol�te si il est appell�)
	/// </summary>
	/// <param name="driverDataTemplate">La data Template de ce driver, qui d�crit l'appareil que ce driver repr�sente</param>
	DoMoDriver(DriverDataTemplate driverDataTemplate);

	//constructeur Obsol�te
	[[deprecated("Ancienne version qui n'utilise pas les DataTemplate, � �viter")]]
	DoMoDriver(std::string name);
	//Constructeur Obsol�te
	[[deprecated("Ancienne version qui n'utilise pas les DataTemplate, � �viter")]]
	DoMoDriver(std::string name, std::vector<int> compoTypes, std::vector<std::string> compoPaths);

	/// <summary>
	/// Le destructeur de ce driver
	/// </summary>
	virtual ~DoMoDriver();

	//Ces 4 fonctions servent juste � factoriser celles donn�es par openVR pour modifier des valeurs
	virtual void setStrProperty(vr::ETrackedDeviceProperty SVRproperty, std::string value);
	virtual void setInt32Property(vr::ETrackedDeviceProperty SVRproperty, int32_t value);
	virtual void setUInt64Property(vr::ETrackedDeviceProperty SVRproperty, uint64_t value);
	virtual void setBoolProperty(vr::ETrackedDeviceProperty SVRproperty, bool value);


	virtual EVRInitError ModernActivation(vr::TrackedDeviceIndex_t unObjectId);

	//Activation obsol�te
	virtual EVRInitError [[deprecated("Ancienne version qui n'utilise pas les DataTemplate, � �viter")]] ObsoleteActivation(vr::TrackedDeviceIndex_t unObjectId);

	virtual void registerProperties(vr::TrackedDeviceIndex_t unObjectId);

	//fonctions requises par l'interface ITrackedDeviceServerDriver, commes donn�es dans le sample, elles ne sont pas utilis�es
	[[maybe_unused]] virtual EVRInitError Activate(vr::TrackedDeviceIndex_t unObjectId);
	[[maybe_unused]] virtual void Deactivate();
	[[maybe_unused]] virtual void EnterStandby();
	[[maybe_unused]] virtual void* GetComponent(const char* pchComponentNameAndVersion);
	[[maybe_unused]] virtual void PowerOff();
	[[maybe_unused]] virtual void DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize);

	/*Ces fonctions g�rent la position (rotation quaternionique et position par vecteur) de l'objet,
	* qrotation est responsable de l'angle et Vecposition[3] de la position.
	*/
	
	/// <summary>
	/// r�cup�re les touches de clavier, utilis� par la versions stub de GetPose uniquement
	/// </summary>
	virtual void GetKeypresses();
	virtual DriverPose_t GetPoseStubmode();	//stubbed
	virtual DriverPose_t GetPoseProvided();	// "vraie" version

	[[maybe_unused]] virtual DriverPose_t GetPose();	//version forc�e par SteamVR et pas utilis�e (d�crite dans interfaceRequires.cpp)
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