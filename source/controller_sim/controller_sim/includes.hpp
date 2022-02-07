/**
* @author Yorick geoffre
* @brief this files has every external dependcy this project needs, this way it's easier to keep track of what is included and stay clear of circular includes
* @version 0.1
* @date 16/12/2021
*/

#pragma once

#include <openvr_driver.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <locale>
#include <codecvt>
#include <string>
#include <vector>		//prend la lib des vecteurs
#include <thread>		//multithreading
#include <chrono>		//heure/temps
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <windows.h>	//si sur windows, on inclut le header du syst�me windows
#include <WinUser.h>	//requis pour les hooks de clavier
#include <stdio.h>
#include <Windows.h>
#include <winnt.h>
#include <list>
#include "atlbase.h"
#include "atlstr.h"
#include "comutil.h"
#include "shlobj_core.h"	//pour trouver %appdata%
#include <sstream>

using namespace vr;		//on utilise l'espace de noms d'openVR � travers tout le projet
using namespace std;	//idem pour l'espace de noms standard

#include "entry_point.h"	//le point d'entr�e du DLL, charg� par SteamVR