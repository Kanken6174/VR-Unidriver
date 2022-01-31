#pragma once
#include "VRComponent.h"

/// <summary>
/// Représente un composant analogique dont la valeur va de 0 à 1 (double)
/// </summary>
class VRAnalog : public VRComponent {
private:
	double value;
	double maxValue;
	double minValue;
	double oldValue;
	//va mettre à jour les minimums et les maximums en fonction de la valeur captée
	void updateMinMax();
public:
	//va mettre à jour la valeur du composant (brute)
	void setValue(double value);
	//va retourner la valeur du composant sous format string
	string to_string();
};