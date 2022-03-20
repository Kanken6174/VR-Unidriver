#pragma once

/// <summary>
/// Ce namespace est utilisé en tant que "système D" pour éviter les limitations d'openvr.h qui est incompatible avec openvr_driver.h
/// </summary>
namespace systemd {
#include<openvr.h>
	void queryForInfoOnDeviceSteamvr();
}