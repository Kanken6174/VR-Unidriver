#include "Formater.h"
using namespace std;
Formater::Formater()
{
	this->format = "";
}

Formater::~Formater()
{
}

/// <summary>
/// Fonction de transformation des informations � envoyer au tunnel nomm� en un string contenant leurs informations
/// </summary>
/// <param name="quat"> un quaternion </param>
/// <param name="delais"> delais d'envois depuis derni�re requ�te </param>
/// <param name="lBouton"> liste des boutons </param>
/// <param name="lTrigger"> listes des Triggers (Joysticks, Potentiom�tre) </param>
void Formater::FormaterDonn�es(Quaternion quat, int delais, list<Bouton> lBouton, list<Trigger> lTrigger)
{
	
	this->format = to_string(delais) + "|" + to_stringQuat(quat) +"|"; /// On ajoute au string "format" le d�but soit le string du d�lais puis du quaternion
	
	for each (object var in lTrigger) /// Ensuite pour chaque �l�ment dans lTrigger, on ajoute son toString a format
	{
		this->format = this->format + toString(var)+"_";
	}

	this->format = this->format.substr(0, this->format.length() - 1); /// pour supprimer le dernier "_"

	this->format = this->format + "|";

	for each (object var in lBouton) /// Finalement on ajoute la liste des boutons
	{
		this->format = this->format + toString(var) + "|";
	}

	this->format = this->format.substr(0, this->format.length() - 1); /// idem qu'avant mais pour le dernier "|"

}

string Formater::to_stringQuat(Quaternion q) {
	
	return to_string(q.getX()) + '_' + to_string(q.getY()) + '_' + to_string(q.getZ()) + '_' + to_string(q.getW());
	

}