#include"utilities.h"

namespace utilities {

	vector<string> split(string input, char splitter) {
		stringstream strs = stringstream(input);
		vector<string> toreturn = vector<string>();
		string segment = "";

		while (getline(strs, segment, splitter))
		{
			toreturn.push_back(segment);
		}

		return toreturn;
	}

	string getDelimitedValueFromRawString(string raw, string delimiter) {
		string toReturn = raw;
		size_t delimiterPosition = raw.find(delimiter);

		if (delimiterPosition == string::npos)	//si pas trouvé
			return "";

		toReturn.erase(0, delimiterPosition + delimiter.size());	//on enlève ce qu'y a avant le delimiterPosition, delimiter compris

		size_t dataEndPosition = toReturn.find_first_not_of("0123456789.-,");

		if (delimiterPosition == string::npos)	//si pas trouvé
			return toReturn;	//c'est que la trame était la dernière

		toReturn.erase(dataEndPosition, toReturn.size());	//on supprime le reste

		return toReturn;
	}

	string getFirstAndRemoveFromVector(vector<string> source) {
		string toReturn = source[0];
		source.erase(std::next(source.begin()));	//on supprime le premier élément (correspond à un comportement de dépilage)
		return toReturn;
	}

	int stringToInt(string input) {
		int toReturn = 0;
		toReturn = stoi(input);
		return toReturn;
	}

	bool stringToBool(string input) {
		bool toReturn = false;
		toReturn = (input[0] == 1);
		return toReturn;
	}

	float stringToFloat(string input) {
		float toReturn = 0;
		toReturn = stof(input);
		return toReturn;
	}

	double stringToDouble(string input) {
		double toReturn = 0;
		toReturn = stod(input);
		return toReturn;
	}

	vector<float> delimitedStringToFloats(string input, char delimiter) {
		vector<float> toReturn = vector<float>();
		vector<string> temp = split(input, delimiter);
		for (string str : temp)
			toReturn.push_back(stringToFloat(str));

		return toReturn;
	}
}