#pragma once
#include"VRComponent.h"

/// <summary>
/// Cette classe repr�sente un composant de type bouton (booleen)
/// </summary>
class VRButton : VRComponent {
private:
	bool ispressed;
public:
	void setValue(bool value);//TODO code
	string to_string();//TODO code
};