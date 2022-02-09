#pragma once
#include"includes.h"

/// <summary>
/// représente un composant abstrait
/// </summary>
class VRComponent{
private:
	vector<char> flag;
	int sclType = -1;
public:
	virtual void settype(int type);
	virtual int gettype();

	virtual void setFlag(vector<char> flag);
	//retourne la position du composant
	virtual vector<char> getFlag();

	//Envoie des données au composant
	virtual void receiveData(string data);

	//retourne le string de la positon du composant
	virtual string to_string();
};