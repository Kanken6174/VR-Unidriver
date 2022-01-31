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
	//va mettre � jour les minimums et les maximums en fonction de la valeur capt�e
	void updateMinMax();
public:
	//va mettre � jour la valeur du composant (brute)
	void setValue(double value);
	//va retourner la valeur du composant sous format string
	string to_string();
};