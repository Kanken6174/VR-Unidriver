#pragma once
#include"includes.h"

/// <summary>
/// représente un composant abstraitc
/// </summary>
class VRComponent {
private:
	int position;
public:
	virtual int getPosition();//retourne la position du composant
	virtual std::string to_string();//retourne le string de la positon du composant
};