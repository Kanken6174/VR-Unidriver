#pragma once
#include "includes.hpp"

//-----------------------------------------Utilitaires---------------------------------------------

namespace utilities {
	vector<string> split(string input, char splitter);
	bool stringToBool(string input);
	float stringToFloat(string input);
	double stringToDouble(string input);
}