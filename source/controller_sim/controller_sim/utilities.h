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
	/// permet de s�parer un string selon un d�lilimteur pr�cis�
	/// </summary>
	/// <param name="input"> le string � s�parer</param>
	/// <param name="splitter"> le caract�re de s�paration (optionnel � '|')</param>
	/// <param name="remove"> (optionnel � false), si on enl�ve le caract�re de s�paration ou pas</param>
	/// <returns>un vecteur contenant les diff�rentes parties du string d'origine</returns>
	vector<string> split(string input, char splitter = '|', bool remove = true);
	/// <summary>
	/// Va prendre le premier string d'un vecteur de string, le retirer de ce vecteur, et le retourner
	/// </summary>
	/// <param name="source">le vecteur de strings � traiter</param>
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