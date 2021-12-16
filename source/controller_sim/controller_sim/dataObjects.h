/**
* @author Yorick Geoffre
* @brief this file holds the declaration of the dataObjects, which contain the info required to create a device driver and some components
* @version 0.1
* @date 16/12/2021
*/

#include <openvr_driver.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <locale>
#include <codecvt>
#include <string>
#include <vector>	//prend la lib des vecteurs
#include <thread>	//multithreading
#include <chrono>	//heure/temps
#include <stdio.h>
#include <stdarg.h>
#include <windows.h>	//si sur windows, on inclut le header du syst�me windows
#include <WinUser.h> //requis pour les hooks de clavier

//Ce fichier contient des formats de donn�es pour les drivers et les composants
//ils servent surtout de stockage temporaire entre la lecture du fichier de config et la cr�ation des vrais objets
//(�a �vite d'avoir des dizaines de vecteurs doubles en vrac)
using namespace std;
using namespace vr;

class ComponentDataTemplate {
public:
	int inputType = 99;		//0-5 pour choisir un vrai mode (analog, bool, skeleton...), 
							//5+ pour le mode stub qui �value l'update � partie de la touche de clavier correspondante
	string inputPath = "";	//Le chemin d'input SVR, exemple /input/a/click
};

class DriverDataTemplate {
public:
	string name = "default_name";	//le nom de l'appareil qui sera ajout�
	string renderModel = "";		//le mod�le 3d de l'appareil (optionnel)
	string serialNumber = "";		//le num�ro de s�rie (r�vision) de l'appareil
	int role = TrackedControllerRole_Invalid;	//d�faut � invalid (0), de 0 � 5 (1 main droite, 2 main gauche)
	vector<ComponentDataTemplate*> components;	//les divers composants du driver (boutons, joysticks, entr�es squelette...)
};