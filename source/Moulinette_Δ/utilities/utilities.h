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
#include <sstream>	//stringstream
#include <regex>

#define ERROR_STOD -2.2250738585072014
#define ERROR_MAJOR -2.2250738585072013

using namespace std;

//-----------------------------------------Utilitaires---------------------------------------------

namespace utilities {
	/// <summary>
	/// permet de s�parer un string selon un d�lilimteur pr�cis�
	/// </summary>
	/// <param name="input"> le string � s�parer</param>
	/// <param name="splitter"> le caract�re de s�paration</param>
	/// <returns>un vecteur contenant les diff�rentes parties du string d'origine</returns>
	vector<string> split(string input, char splitter);
	/// <summary>
	/// Va prendre le premier string d'un vecteur de string, le retirer de ce vecteur, et le retourner
	/// </summary>
	/// <param name="source">le vecteur de strings � traiter</param>
	/// <returns>le premier string du vecteur</returns>
	string getFirstAndRemoveFromVector(vector<string> source);
	string getDelimitedValueFromRawString(string raw, string delimiter);
	int stringToInt(string input);
	bool stringToBool(string input);
	float stringToFloat(string input);
	double stringToDouble(string input);
	char* stringToChar(string U);
}