#pragma once
#include"includes.h"
#include"VRComponent.h"
#include"../../Madgwick Rotations/Madgwick Rotations/MadgwickRotator.h"

/// <summary>
/// Cette classe représente le quaternion de rotation d'un appareil unique, il en existe un par appareil et il est construit
/// à partir des données de gyroscope, d'accéléromètre, et de magnetomètre
/// </summary>
class VRQuaternion : public VRComponent {
private:
	//Le quaternion de rotation du composant
	Quaternion value = Quaternion();
	//l'instance de MadgwickRotator qui s'occupe de créer le quaternion value
	MadgwickRotator transformator = MadgwickRotator();

	void setValue(time_t delay, madgwickRotations::Vector acc, madgwickRotations::Vector mag, madgwickRotations::Vector gyro);
public:
	VRQuaternion(float accCorrectionStrength, float magCorrectionStrength);
	VRQuaternion();

	string to_string() override;
	
	void receiveData(string data) override;
};