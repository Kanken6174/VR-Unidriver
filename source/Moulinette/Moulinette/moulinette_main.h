#pragma once

#include <list>
#include <string>
#include "moulinette_components.h"
#include "../../SerialPort/SerialPort/Device.h"

namespace moulinette_main {
	class Manager;

	class Transformer;

	class Device;

	std::list<moulinette_components::VRComponent> buildComponents(serialport::Device* devices[]);

	std::string prepare(std::list<Device>* devices);
}