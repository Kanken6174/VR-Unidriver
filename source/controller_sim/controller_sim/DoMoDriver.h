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

	///Constructeurs et destructeurs
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

	///Fonctions d'activation du driver SteamVR
		/// <summary>
		/// Cette fonction va activer et enregistrer le driver aupr�s de SteamVR, � partir des DataTemplates enregistr�es en interne
		/// </summary>
		/// <param name="unObjectId"></param>
		/// <returns></returns>
		virtual EVRInitError ModernActivation(vr::TrackedDeviceIndex_t unObjectId);

		//Fonction d'activation obsol�te
		virtual EVRInitError [[deprecated("Ancienne version qui n'utilise pas les DataTemplate, � �viter")]] ObsoleteActivation(vr::TrackedDeviceIndex_t unObjectId);

	virtual void registerProperties(vr::TrackedDeviceIndex_t unObjectId);

	///fonctions requises par l'interface ITrackedDeviceServerDriver, commes donn�es dans le sample, elles ne sont pas utilis�es
		[[maybe_unused]] virtual EVRInitError Activate(vr::TrackedDeviceIndex_t unObjectId);
		[[maybe_unused]] virtual void Deactivate();
		[[maybe_unused]] virtual void EnterStandby();
		[[maybe_unused]] virtual void* GetComponent(const char* pchComponentNameAndVersion);
		[[maybe_unused]] virtual void PowerOff();
		[[maybe_unused]] virtual void DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize);

	///Ces fonctions g�rent la position (rotation quaternionique et position par vecteur) de l'objet,qrotation est responsable de l'angle et Vecposition[3] de la position.
		/// <summary>
		/// r�cup�re les touches de clavier, utilis� par la versions stub de GetPose uniquement
		/// </summary>
		virtual void GetKeypresses();
		/// <summary>
		/// appelle GetKeypresses() et r�cup�re les informations d'angle d'euler et de position puis en fait une pose.
		/// </summary>
		/// <returns> Une pose Steamvr DriverPose_t</returns>
		virtual DriverPose_t GetPoseStubmode();	//stubbed
		/// <summary>
		/// recup�re les informations locales de quaternion et de position (obtenus via le tunnel nomm� normalement) et en fait une pose
		/// </summary>
		/// <returns> Une pose Steamvr DriverPose_t</returns>
		virtual DriverPose_t GetPoseProvided();	// "vraie" version
		
		/// <summary>
		/// version forc�e par SteamVR et pas utilis�e (d�crite dans interfaceRequires.cpp), ne devrait pas �tre utilis�e
		/// </summary>
		/// <returns> Une pose Steamvr DriverPose_t</returns>
		[[maybe_unused]] virtual DriverPose_t GetPose();
	
	///Les fonctions ici g�rent la mise � jour des donn�es � chaque frame-----------------------------------------------------------------
		/// <summary>
		/// Cette fonction g�re la mise � jour des valeurs d'entr�e � chaque frame du jeu (version stub)
		/// </summary>
		virtual void RunFrameStub();
		/// <summary>
		/// Cette fonction g�re la mise � jour des valeurs d'entr�e � chaque frame du jeu
		/// </summary>
		/// <param name="raw">Un string contenant toutes les valeurs relatives � cet appareil (trame de driver standard)</param>
		virtual void RunFrameRaw(string raw);
	///fonctions requises par l'interface de SteamVR (peut �tre non-utilis�)---------------------------------------------------------------
		/// <summary>
		/// Requis par SteamVR, renvoie l'identifiant unique de l'appareil (d�crit dans InterfaceRequires.h)
		/// </summary>
		/// <returns>L'identifiant de l'appareil</returns>
		virtual std::string GetSerialNumber();
	///fonction de mise � jour des valeurs internes
		/// <summary>
		/// Cette fonction g�re la mise � jour de valeurs par celles re�ues du tunnel nomm� (appell�e par RunFrameRaw())
		/// </summary>
		/// <param name="pipeData">la trame contenant toutes les valeurs relatives � cet appareil</param>
		/// <returns>les valeurs de chaque composant, avec les valeurs relatives � l'appareil (latence, orientation) retir�es car d�j� appliqu�es</returns>
		virtual vector<string> UpdateInternalValuesFromPipedData(string pipeData);
};