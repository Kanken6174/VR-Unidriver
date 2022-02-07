/**
* @author Yorick Geoffre
* @brief defines a single device, which can be host to multiple component and has a pose (rotation + position) in 3d space
* @version 0.5
* @date 16/12/2021
*/

#include "DoMoDriver.h"


	DoMoDriver::DoMoDriver(DriverDataTemplate ddt) {
		DriverLog("Started building %s by DriverDataTemplate", ddt.name.c_str());
		this->PosOffsets[0] = rand() % (3 - -3 + 1) + -3; // Generate the number, assign to variable. 0-2
		this->PosOffsets[1] = rand() % (3 - -3 + 1) + -3; // Generate the number, assign to variable.
		this->PosOffsets[2] = rand() % (3 - -3 + 1) + -3; // Generate the number, assign to variable.
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

	EVRInitError DoMoDriver::Activate(vr::TrackedDeviceIndex_t unObjectId)
	{
		ModernActivation(unObjectId);
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