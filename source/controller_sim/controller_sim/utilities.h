#pragma once
#include "includes.hpp"

//-----------------------------------------Utilitaires---------------------------------------------

namespace utilities {
	vector<string> split(string input, char splitter);
	string getFirstAndRemoveFromVector(vector<string> source);
	HmdQuaternion_t* stringToQuaternion(string input, char splitter);
	int stringToInt(string input);
	bool stringToBool(string input);
	float stringToFloat(string input);
	double stringToDouble(string input);
}