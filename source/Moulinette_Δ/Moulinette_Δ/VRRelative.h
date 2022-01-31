#pragma once
#include "VRComponent.h"

/// <summary>
/// Repr�sente un composant analogique dont la valeur va de -1 � 1 (double)
/// </summary>
class VRRelative : public VRComponent {
private:
	double value;
	double maxValue;
	double minValue;
	double oldValue;
	void updateMinMax();//TODO code
public:
	void setValue(double value);//TODO code
	string to_string();//TODO code
};