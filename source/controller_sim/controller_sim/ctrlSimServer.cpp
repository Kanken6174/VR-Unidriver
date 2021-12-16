/**
* @author Yorick Geoffre
* @brief this file holds the declaration of the main server driver, which possesses all other devices and subsequent components, and passes the pointers to SteamVR
* @version 0.7
* @date 16/12/2021
*/

#include "controller_sim.h"

using namespace vr;



/**
* reference: https://github.com/ValveSoftware/openvr/wiki/IServerTrackedDeviceProvider_Overview
* Il s'agit du serveur qui va contrôler les différents appareils, car il peut y en avoir plusieurs par
* serveur.
*/
EVRInitError Controller_simDriverServer::Init(vr::IVRDriverContext* pDriverContext)
{
	VR_INIT_SERVER_DRIVER_CONTEXT(pDriverContext);	//une fonction définie dans openvr_driver.h
	InitDriverLog(vr::VRDriverLog());	//initialise le logging d'informations visible sur la console web

	DriverLog("log inited\n");
	ReadConfigAndBuildDrivers();
	DriverLog("driver(s) inited\n");
	RegisterInternalDrivers();
	DriverLog("driver(s) registered");
	inited = true;

	return VRInitError_None;
}

std::wstring ExePath() {
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	return std::wstring(buffer).substr(0, pos);
}

void Controller_simDriverServer::ReadConfigAndBuildDrivers() {
	std::ifstream driverCfgFile;	//create readonly stream
	driverCfgFile.open("C:\\Users\\ASUS\\Documents\\2A\\projet\\domocap\\source\\controller_sim\\ressources\\controller_sim\\bin\\win64\\driverCfg.dmc");	//proprietary config file -> .doMoCap -> .dmc

	if (!driverCfgFile) {
		//on récupère le chemin courant et on le convertit en string
		DriverLog("Unable to open driver config file from path: %s",ExePath().c_str());
		return;
	}

	std::vector<DriverDataTemplate*> DriverTemplates;

	int activeDriverVector = -1;
	int activeCompomentVector = -1;

	//la déclaration des variables (même intermédiaires), doit se faire avant le switch/case en c++, d'où ces 3 déclarations:
	DriverDataTemplate* DriverTemp = nullptr;
	ComponentDataTemplate* CompoTemp = nullptr;
	int intBuf = 99;
	std::string buf = "";

	while (std::getline(driverCfgFile, buf)) {
		char id = buf[0];
		buf = buf.erase(0, 1);
		buf.erase(std::remove(buf.begin(), buf.end(), '\n'), buf.end()); //on enlève les \n parasites
		switch (id) {
		case '$':	//nouveau driver
			activeDriverVector++;
			activeCompomentVector = -1;

			DriverTemp = new DriverDataTemplate;
			DriverTemplates.push_back(DriverTemp);
			DriverTemplates[activeDriverVector]->name = buf;

			DriverLog(("Discovered driver named : " + buf).c_str());
			break;
		case '>':	//modèle 3d du driver
			DriverTemplates[activeDriverVector]->renderModel = buf;
			break;
		case '<':	//nature du driver (quelle main entre autres)
			intBuf = std::stoi(buf);
			DriverTemplates[activeDriverVector]->role = intBuf;
			break;
		case '=':	//nouveau composant pour le driver, la ligne commençant par = contient le chemin d'input du driver, ex: /input/a/click
			activeCompomentVector++;
			CompoTemp = new ComponentDataTemplate;
			DriverTemplates[activeDriverVector]->components.push_back(CompoTemp);
			DriverTemplates[activeDriverVector]->components[activeCompomentVector]->inputPath = buf;
			break;
		case ':':	//le type d'input du driver (0-5 pour digital, analog, ect...; 5+ pour bool stub mode)
			intBuf = std::stoi(buf);
			DriverTemplates[activeDriverVector]->components[activeCompomentVector]->inputType = intBuf;
			break;
		case '#': 
					//this is a .dmc comment line, it will be ignored
			break;
		case '@':	// this is a "noisy" comment, it will be displayed in the driver log, useful for debugging
			DriverLog(buf.c_str());
			break;
		default:
			break;
		}
	}
	driverCfgFile.close();
	DriverLog("Found %d drivers", DriverTemplates.size());
	DriverLog("============================================");
	for (DriverDataTemplate* dtemp : DriverTemplates) {
		DriverLog("Driver named : %s has %d components with role %d", dtemp->name.c_str(), dtemp->components.size(), dtemp->role);

		for (ComponentDataTemplate* ctemp : dtemp->components) {
			DriverLog("Component with type : %d at path %s", ctemp->inputType, ctemp->inputPath.c_str());
		}
		DriverLog("------------------------------------------");
		DoMoDriver* driver = new DoMoDriver(*dtemp);
		Controller_simDriverServer::Drivers.push_back(driver);
		DriverLog("============================================");
	}
	DriverLog("Created %d drivers", Drivers.size());
}



void Controller_simDriverServer::RegisterInternalDrivers() {
	for (DoMoDriver* driver : Controller_simDriverServer::Drivers) {
		bool success = vr::VRServerDriverHost()->TrackedDeviceAdded(driver->GetSerialNumber().c_str(), vr::TrackedDeviceClass_Controller, driver);
		if (success)
			DriverLog("driver registered successfully\n");
		else
			DriverLog("Failed to register driver");
	}
}

void Controller_simDriverServer::Cleanup()
{
	inited = false;
	CleanupDriverLog();

	for (DoMoDriver* driver : Controller_simDriverServer::Drivers)
		driver->~DoMoDriver();	//appel de destructeur
}

const char* const* Controller_simDriverServer::GetInterfaceVersions()
{
	return vr::k_InterfaceVersions;
}

void Controller_simDriverServer::RunFrame()
{
	if (inited) {
		for (DoMoDriver* driver : Controller_simDriverServer::Drivers)
			driver->RunFrame();
	}
	else {
		DriverLog("Not inited yet!");
	}

	vr::VREvent_t vrEvent;
	while (vr::VRServerDriverHost()->PollNextEvent(&vrEvent, sizeof(vrEvent)))
	{
	}
}
bool Controller_simDriverServer::ShouldBlockStandbyMode() { return false; }
void Controller_simDriverServer::EnterStandby() {/*standby code for the gloves here??*/ }
void Controller_simDriverServer::LeaveStandby() {/*Wake up for the gloves here?*/ }


Controller_simDriverServer controller_simServer;	//c'est global, c'est moche, c'est SteamVR

/**
* La fonction qui sera exportée vers OpenVR, il s'agit de
* notre point d'entrée! (void main() en gros)
*
* Elle va récupérer des pointeurs vers des classes prédéfinies pour les charger dans SVR
*/
HMD_DLL_EXPORT FUNCTION_POINTER HmdDriverFactory(const char* pInterfaceName, int* pReturnCode)
{
	if (0 == strcmp("IServerTrackedDeviceProvider_004", pInterfaceName))	//on vérifie que le nom d'interface correspond
	{
		return &controller_simServer;	//on renvoie l'addresse de la classe du serveur du driver
	}

	if (0 == strcmp(IVRWatchdogProvider_Version, pInterfaceName))
	{
		return NULL;	//on a pas de watchdog dans ce driver, comme on fait pas tourner de code en arrière-plan
	}

	if (pReturnCode)
		*pReturnCode = 105;	//cette valeur correspond à VRInitError_Init_InterfaceNotFound dans openvr_driver.h enum

	return NULL;
}