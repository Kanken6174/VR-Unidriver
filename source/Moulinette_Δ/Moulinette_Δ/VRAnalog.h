#pragma once
#include "VRComponent.h"

/// <summary>
/// Repr�sente un composant analogique dont la valeur va de 0 � 1 (double)
/// </summary>
class VRAnalog : public VRComponent {
private:
	double value;
	double maxValue;
	double minValue;
	double oldValue;
	void updateMinMax();//va mettre � jour les minimums et les maximums en fonction de la valeur capt�e
public:
	void setValue(double value);	//va mettre � jour la valeur du composant (brute)
	std::string to_string();	//va retourner la valeur du composant sous format string
};