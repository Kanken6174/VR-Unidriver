#include "controller_sim.h"

namespace utilities {
	//Convertit un string en LPWSTR
	LPWSTR strToLPW(string toConvert) {
		LPWSTR converted = NULL;
		const char* toConvertBuff = toConvert.c_str();
		size_t converted_chars = 0;
		TCHAR resultBuff[1000];
		mbstowcs_s(&converted_chars, resultBuff, strlen(toConvertBuff) + 1, toConvertBuff, _TRUNCATE);

		converted = resultBuff;

		return converted;
	}

	//Autre méthode, possiblement non-thread safe
	LPWSTR strToLPW_MB(string toConvert) {
		wchar_t* output = nullptr;
		
		int lenA = 0;
		int lenW = 0;

		lenA = lstrlenA(toConvert.c_str());
		lenW = MultiByteToWideChar(CP_ACP, 0, toConvert.c_str(), lenA, NULL, 0);
		if (lenW > 0)
		{
			output = new wchar_t[lenW];
			MultiByteToWideChar(CP_ACP, 0, toConvert.c_str(), lenA, output, lenW);
		}
		LPWSTR out = output;
	}

	//encore une autre méthode, utilisant CA2CT, c'est une covnersion ATL assez ancienne, mais elle devrait marcher
	LPWSTR strToLPW_CA(string toConvert) {
		return CA2CT(toConvert.c_str());
	}
}