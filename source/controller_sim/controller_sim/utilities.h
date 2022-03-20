/**
* @author Yorick Geoffre
* @brief describes various utilities, specifically string-related ones
* @version 0.1
* @date 16/12/2021
*/

#pragma once
#include "includes.hpp"

//-----------------------------------------Utilitaires---------------------------------------------

namespace utilities {
	/// <summary>
	/// permet de séparer un string selon un délilimteur précisé
	/// </summary>
	/// <param name="input"> le string à séparer</param>
	/// <param name="splitter"> le caractère de séparation (optionnel à '|')</param>
	/// <param name="remove"> (optionnel à false), si on enlève le caractère de séparation ou pas</param>
	/// <returns>un vecteur contenant les différentes parties du string d'origine</returns>
	vector<string> split(string input, char splitter = '|', bool remove = true);
	/// <summary>
	/// Va prendre le premier string d'un vecteur de string, le retirer de ce vecteur, et le retourner
	/// </summary>
	/// <param name="source">le vecteur de strings à traiter</param>
	/// <returns>le premier string du vecteur</returns>
	string getFirstAndRemoveFromVector(vector<string> source);
	HmdQuaternion_t* stringToQuaternion(string input, char splitter);
	int stringToInt(string input);
	bool stringToBool(string input);
	float stringToFloat(string input);
	double stringToDouble(string input);

	vector<double> delimitedStringToDoubles(string input, char delimiter = '|');
	vector<float> delimitedStringToFloats(string input, char delimiter = '|');

	void logAllDevices();
	TrackedDevicePose_t getPoseFromID(TrackedDeviceIndex_t id);
}