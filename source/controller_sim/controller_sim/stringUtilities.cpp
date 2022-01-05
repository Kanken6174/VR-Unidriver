#include"controller_sim.h"

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