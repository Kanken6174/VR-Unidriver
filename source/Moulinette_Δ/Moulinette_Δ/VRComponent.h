#pragma once
#include"includes.h"

/// <summary>
/// représente un composant abstrait
/// </summary>
class VRComponent {
private:
	int position = 0;
	int sclType = -1;
public:
	virtual void settype(int type);
	virtual int gettype();
	//retourne la position du composant
	virtual int getPosition();
	//retourne le string de la positon du composant
	virtual std::string to_string();
};