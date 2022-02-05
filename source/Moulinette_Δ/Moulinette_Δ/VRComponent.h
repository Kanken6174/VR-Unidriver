#pragma once
#include"includes.h"

/// <summary>
/// représente un composant abstrait
/// </summary>
class VRComponent{
private:
	string flag;
	int sclType = -1;
public:
	virtual void settype(int type);
	virtual int gettype();

	virtual void setFlag(string flag);
	//retourne la position du composant
	virtual string getFlag();

	//Envoie des données au composant
	virtual void receiveData(string data);

	//retourne le string de la positon du composant
	virtual string to_string();
};