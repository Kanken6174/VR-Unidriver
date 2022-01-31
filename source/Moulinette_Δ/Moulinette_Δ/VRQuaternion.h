#pragma once
#include"includes.h"
#include"VRComponent.h"
#include"../../madgwickRotations library/MadgwickRotator.h"

/// <summary>
/// Cette classe repr�sente le quaternion de rotation d'un appareil unique, il en existe un par appareil et il est construit
/// � partir des donn�es de gyroscope, d'acc�l�rom�tre, et de magnetom�tre
/// </summary>
class VRQuaternion : public VRComponent {
private:
	//Le quaternion de rotation du composant
	Quaternion value = Quaternion();
	//l'instance de MadgwickRotator qui s'occupe de cr�er le quaternion value
	MadgwickRotator transformator = MadgwickRotator();
public:
	void setValue(madgwickRotations::Vector acc, madgwickRotations::Vector mag, madgwickRotations::Vector gyro);
	string to_string();
};