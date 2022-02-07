#include"utilities.h"

namespace utilities {

	vector<string> split(string input, char splitter, bool remove) {
		stringstream strs = stringstream(input);
		vector<string> toreturn = vector<string>();
		string segment = "";

		if (input.find(splitter) == std::string::npos) {	//delimiter not found
			toreturn.push_back(input);
			return toreturn;
		}

		while (getline(strs, segment, splitter))
		{
			toreturn.push_back(segment);
		}

		if (remove) {
			for (string str : toreturn) {
				str.erase(std::remove(str.begin(), str.end(), splitter), str.end());
			}
		}

		return toreturn;
	}

	string getFirstAndRemoveFromVector(vector<string> source) {
		string toReturn = source[0];
		source.erase(std::next(source.begin()));	//on supprime le premier élément (correspond à un comportement de dépilage)
		return toReturn;
	}

	HmdQuaternion_t* stringToQuaternion(string input, char splitter) {
		vector<string> values = split(input, splitter);
		if (values.size() < 4)
			return new HmdQuaternion_t();	//0,0,0,0 si on a une erreur
		
		HmdQuaternion_t* quat = new HmdQuaternion_t();
		
		quat->x = (values[0].find_first_not_of("0123456789.-") == std::string::npos) ? stringToDouble(values[0]) : 0;
		quat->y = (values[1].find_first_not_of("0123456789.-") == std::string::npos) ? stringToDouble(values[1]) : 0;
		quat->z = (values[2].find_first_not_of("0123456789.-") == std::string::npos) ? stringToDouble(values[2]) : 0;
		quat->w = (values[3].find_first_not_of("0123456789.-") == std::string::npos) ? stringToDouble(values[3]) : 0;

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
		try {
			toReturn = stod(input);
		}
		catch (exception e) {
			//log?
			return -1;
		}
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