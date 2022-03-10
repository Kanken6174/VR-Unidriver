#pragma once
#include "componentHeaders.h"	

/// <summary>
/// Représente un composant analogique dont la valeur va de -1 à 1 (double)
/// </summary>
class VRRelative : public VRComponent {
private:
	double value = 0;
	double maxValue = 0;
	double minValue = 0;
	double oldValue = 0;
	//va mettre à jour les minimums et les maximums en fonction de la valeur captée
	void updateMinMax();
	//va mettre à jour la valeur du composant (brute)
	void setValue(double value);
	double getValue();
	void setValueOld(double value);
	double getValueOld();

public:
	VRRelative();
	void setMin(double value);
	void setMax(double value);
	void receiveData(string data) ;
	//va retourner la valeur du composant sous format string
	string to_string() ;
};