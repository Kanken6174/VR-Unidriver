#include "controller_sim.h"

using namespace std;
using namespace vr;

namespace utilities {

	wstring ExePath() {
		TCHAR buffer[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, buffer, MAX_PATH);
		std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
		return std::wstring(buffer).substr(0, pos);
	}

	vector<DriverDataTemplate*>* ReadConfigAndBuildDrivers() {
		ifstream driverCfgFile;	//create readonly stream
		char* usrname = nullptr;
		size_t sz = 0;
		_dupenv_s(&usrname, &sz, "username");
		string filePath = "C:\\Users\\"+string(usrname)+"\\AppData\\Roaming\\.DoMoCap\\driverCfg.dmc";	//full path
		DriverLog(("Opening configuration file from "+filePath).c_str());
		driverCfgFile.open(filePath);	//proprietary config file -> .doMoCap -> .dmc

		if (!driverCfgFile) {
			//on récupère le chemin courant et on le convertit en string
			DriverLog("Unable to open driver config file from path: %s", filePath.c_str());
			return new vector<DriverDataTemplate*>();
		}

		vector<DriverDataTemplate*>* DriverTemplates = new vector<DriverDataTemplate*>();

		int activeDriverVector = -1;
		int activeCompomentVector = -1;

		//la déclaration des variables (même intermédiaires), doit se faire avant le switch/case en c++, d'où ces 3 déclarations:
		DriverDataTemplate* DriverTemp = nullptr;
		ComponentDataTemplate* CompoTemp = nullptr;
		int intBuf = 99;
		std::string buf = "";

		vector<double> doubleVector = vector<double>();

		bool toignore = false;

		while (std::getline(driverCfgFile, buf)) {
			char id = buf[0];
			buf = buf.erase(0, 1);
			buf.erase(std::remove(buf.begin(), buf.end(), '\n'), buf.end()); //on enlève les \n parasites
			try {
				switch (id) {
				case '$':	//nouveau driver
					toignore = false;
					activeDriverVector++;
					activeCompomentVector = -1;

					DriverTemp = new DriverDataTemplate;
					DriverTemp->name = buf;
					DriverTemplates->push_back(DriverTemp);

					DriverLog(("Discovered driver named : " + buf).c_str());
					break;
				case '>':	//modèle 3d du driver
					if (DriverTemplates->at(activeDriverVector)->role == 2) {
						DriverLog("Switched to hardcoded render path");
						DriverTemplates->at(activeDriverVector)->renderModel = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\SteamVR\\resources\\rendermodels\\vr_glove\\vr_glove_left_model.glb";
					}
					else {
						DriverTemplates->at(activeDriverVector)->renderModel = buf;
					}
					break;
				case '<':	//nature du driver (quelle main entre autres)
					intBuf = stoi(buf);
					DriverTemplates->at(activeDriverVector)->role = intBuf;
					break;
				case '%':	//handle de l'appareil à shadow
					DriverTemplates->at(activeDriverVector)->handleToShadow = stoi(buf);
					break;
				case '|':	//si on doit shadow la rotation
					DriverTemplates->at(activeDriverVector)->shadowRotation = (buf.find("true") != std::string::npos);
					break;
				case '_':	//si on doit shadow la position
					DriverTemplates->at(activeDriverVector)->shadowRotation = (buf.find("true") != std::string::npos);
					break;
				case '{':	//translation depuis la tête
					doubleVector = delimitedStringToDoubles(buf);
					DriverTemp = DriverTemplates->at(activeDriverVector);
					DriverTemp->vecDriverFromHeadTranslation[0] = doubleVector[0];
					DriverTemp->vecDriverFromHeadTranslation[1] = doubleVector[1];
					DriverTemp->vecDriverFromHeadTranslation[2] = doubleVector[2];
					DriverTemplates->at(activeDriverVector) = DriverTemp;
					DriverLog("Current device has vecDriverFromHeadTranslation = {%f,%f,%f}", doubleVector[0], doubleVector[1], doubleVector[2]);
					break;
				case '}':	//translation depuis le monde
					doubleVector = delimitedStringToDoubles(buf);
					DriverTemp = DriverTemplates->at(activeDriverVector);
					DriverTemp->vecWorldFromDriverTranslation[0] = doubleVector[0];
					DriverTemp->vecWorldFromDriverTranslation[1] = doubleVector[1];
					DriverTemp->vecDriverFromHeadTranslation[2] = doubleVector[2];
					DriverTemplates->at(activeDriverVector) = DriverTemp;
					DriverLog("Current device has vecWorldFromDriverTranslation = {%f,%f,%f}", doubleVector[0], doubleVector[1], doubleVector[2]);
					break;
				case '[':	//rotation depuis la tête
					doubleVector = delimitedStringToDoubles(buf);
					DriverTemp = DriverTemplates->at(activeDriverVector);
					DriverTemp->qDriverFromHeadRotation[0] = doubleVector[0];
					DriverTemp->qDriverFromHeadRotation[1] = doubleVector[1];
					DriverTemp->qDriverFromHeadRotation[2] = doubleVector[2];
					DriverTemplates->at(activeDriverVector) = DriverTemp;
					DriverLog("Current device has qDriverFromHeadRotation = {%f,%f,%f}", doubleVector[0], doubleVector[1], doubleVector[2]);
					break;
				case ']':	//translation depuis la tête
					doubleVector = delimitedStringToDoubles(buf);
					DriverTemp = DriverTemplates->at(activeDriverVector);
					DriverTemp->qWorldFromDriverRotation[0] = doubleVector[0];
					DriverTemp->qWorldFromDriverRotation[1] = doubleVector[1];
					DriverTemp->qWorldFromDriverRotation[2] = doubleVector[2];
					DriverTemplates->at(activeDriverVector) = DriverTemp;
					DriverLog("Current device has qWorldFromDriverRotation = {%f,%f,%f}", doubleVector[0], doubleVector[1], doubleVector[2]);
					break;
				case '/':	//offset de position
					doubleVector = delimitedStringToDoubles(buf);
					DriverTemp = DriverTemplates->at(activeDriverVector);
					DriverTemp->positionsOffsets[0] = doubleVector[0];
					DriverTemp->positionsOffsets[1] = doubleVector[1];
					DriverTemp->positionsOffsets[2] = doubleVector[2];
					DriverTemplates->at(activeDriverVector) = DriverTemp;
					DriverLog("Current device has positionsOffsets = {%f,%f,%f}", doubleVector[0], doubleVector[1], doubleVector[2]);
					break;
				case '=':	//nouveau composant pour le driver, la ligne commençant par = contient le chemin d'input du driver, ex: /input/a/click
					if (buf[1] == 'p') {	// /pose/... ignoré, on vérifie le p car ce sera différent de /input/ et /ouput/
						toignore = true;
						DriverLog("an incorrectly pathed component was ignored (path = %s)", buf);
					}
					else {
						toignore = false;
						activeCompomentVector++;
						CompoTemp = new ComponentDataTemplate;
						DriverTemplates->at(activeDriverVector)->components.push_back(CompoTemp);
						DriverTemplates->at(activeDriverVector)->components[activeCompomentVector]->inputPath = buf;
					}
					break;
				case ':':	//le type d'input du driver (0-5 pour digital, analog, ect...; 5+ pour bool stub mode)
					if (!toignore) {
						intBuf = stoi(buf);
						DriverTemplates->at(activeDriverVector)->components[activeCompomentVector]->inputType = intBuf;
					}
					break;
				case '#':
					//this is a .dmc comment line, it will be ignored, any unrecognized symbol will also be ignored
					break;
				case '@':	// this is a "noisy" comment, it will be displayed in the driver log, useful for debugging
					DriverLog(buf.c_str());
					break;
				default:
					break;
				}
			}
			catch (out_of_range e) {
				DriverLog("Caught out of range exception with char %c while loading DMC", id);
			}
		}
		driverCfgFile.close();

		return DriverTemplates;
	}

	vector<DoMoDriver*>* makeDriversFromTemplates(vector<DriverDataTemplate*>* DriverTemplates) {
		vector<DoMoDriver*>* drivers = new vector<DoMoDriver*>();
		DriverLog("Found %d drivers", DriverTemplates->size());
		DriverLog("============================================");
		for (DriverDataTemplate* dtemp : *DriverTemplates) {
			DriverLog("Driver named : %s has %d components with role %d", dtemp->name.c_str(), dtemp->components.size(), dtemp->role);

			for (ComponentDataTemplate* ctemp : dtemp->components) {
				DriverLog("Component with type : %d at path %s", ctemp->inputType, ctemp->inputPath.c_str());
			}
			DriverLog("------------------------------------------");
			DoMoDriver* driver = new DoMoDriver(*dtemp);
			drivers->push_back(driver);
			DriverLog("============================================");
		}
		DriverLog("Created %d drivers", drivers->size());

		return drivers;
	}

}