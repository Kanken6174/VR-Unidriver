#pragma once
#include"includes.h"

/// <summary>
/// représente un composant abstrait
/// </summary>
class VRComponent{
private:
	int position = 0;
	int sclType = -1;
public:
	virtual void settype(int type);
	virtual int gettype();

	virtual void setPosition(int position);
	//retourne la position du composant
	virtual int getPosition();

	//Envoie des données au composant
	virtual void receiveData(string data);

	//retourne le string de la positon du composant
	virtual string to_string();
};