#pragma once

/// <summary>
/// Ce namespace est utilis� en tant que "syst�me D" pour �viter les limitations d'openvr.h qui est incompatible avec openvr_driver.h
/// </summary>
namespace systemd {
#include<openvr.h>
	void queryForInfoOnDeviceSteamvr();
}