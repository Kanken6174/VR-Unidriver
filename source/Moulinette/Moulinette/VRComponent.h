#pragma once

#include "moulinette_components.h"
#include <string>

class moulinette_components::VRComponent
{
private:
	int position;

public:
	VRComponent(int position);
	int getPosition();
	virtual std::string to_string() = 0;
};