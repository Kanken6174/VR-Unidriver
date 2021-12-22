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
}