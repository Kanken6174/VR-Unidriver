#pragma once
#include"VRComponent.h"

/// <summary>
/// Cette classe représente un composant de type bouton (booleen)
/// </summary>
class VRBoolean : VRComponent {
private:
	bool value;
public:
	//va changer la valeur du composant (true ou false)
	void setValue(bool value);
	//va retourner la valeur du composant en tant que string
	string to_string();
};