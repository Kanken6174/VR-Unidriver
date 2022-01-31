#pragma once
#include"includes.h"
#include"VRComponent.h"
#include"../../madgwickRotations library/MadgwickRotator.h"

class VRQuaternion : public VRComponent {
private:
	Quaternion value;
};