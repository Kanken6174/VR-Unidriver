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

	string getFirstAndRemoveFromVector(vector<string> source) {
		string toReturn = source[0];
		source.erase(std::next(source.begin()));	//on supprime le premier �l�ment (correspond � un comportement de d�pilage)
		return toReturn;
	}

	HmdQuaternion_t* stringToQuaternion(string input, char splitter) {
		vector<string> values = split(input, splitter);
		if (values.size() < 4)
			return new HmdQuaternion_t();	//0,0,0,0 si on a une erreur
		
		HmdQuaternion_t* quat = new HmdQuaternion_t();
		
		quat->x = stringToDouble(values[0]);
		quat->y = stringToDouble(values[1]);
		quat->z = stringToDouble(values[2]);
		quat->w = stringToDouble(values[3]);

		return quat;
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