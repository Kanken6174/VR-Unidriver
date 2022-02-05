#pragma once
#include"VRComponent.h"

/// <summary>
/// Cette classe représente un composant de type bouton (booleen)
/// </summary>
class VRBoolean : public VRComponent {
private:
	bool value = false;
	//va changer la valeur du composant (true ou false)
	void setValue(bool value);
public:
	VRBoolean();

	void receiveData(string data) override;
	//va retourner la valeur du composant en tant que string
	string to_string() override;
};