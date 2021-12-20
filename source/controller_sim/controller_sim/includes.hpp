#pragma once

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
#include <windows.h>	//si sur windows, on inclut le header du système windows
#include <WinUser.h> //requis pour les hooks de clavier
#include <stdio.h>
#include <Windows.h>
#include <winnt.h>

#include "entry_point.h"

using namespace vr;
using namespace std;