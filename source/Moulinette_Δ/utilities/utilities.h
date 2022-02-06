/**
* @author Yorick Geoffre
* @brief describes various utilities, specifically string-related ones
* @version 0.1
* @date 16/12/2021
*/

#pragma once
#include<string>
#include<vector>
#include <fstream>
#include "atlbase.h"
#include "atlstr.h"
#include <sstream>	//stringstream
#include <regex>

using namespace std;

//-----------------------------------------Utilitaires---------------------------------------------

namespace utilities {
	/// <summary>
	/// permet de séparer un string selon un délilimteur précisé
	/// </summary>
	/// <param name="input"> le string à séparer</param>
	/// <param name="splitter"> le caractère de séparation</param>
	/// <returns>un vecteur contenant les différentes parties du string d'origine</returns>
	vector<string> split(string input, char splitter);
	/// <summary>
	/// Va prendre le premier string d'un vecteur de string, le retirer de ce vecteur, et le retourner
	/// </summary>
	/// <param name="source">le vecteur de strings à traiter</param>
	/// <returns>le premier string du vecteur</returns>
	string getFirstAndRemoveFromVector(vector<string> source);
	int stringToInt(string input);
	bool stringToBool(string input);
	float stringToFloat(string input);
	double stringToDouble(string input);
}