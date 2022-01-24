#pragma once

#include "moulinette_components.h"
#include "VRComponent.h"
#include "../../madgwickRotations library/Quaternion.h"

using namespace madgwickRotations;
using namespace moulinette_components;

class moulinette_components::VRQuaternion : public VRComponent
{
private:
	Quaternion* quaternion;

public:
	VRQuaternion(int position, Quaternion* quaternion);
	~VRQuaternion();
	std::string to_string() override;
};