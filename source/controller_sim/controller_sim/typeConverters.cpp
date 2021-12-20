#include "controller_sim.h"

namespace utilities {
	LPWSTR strToLPW(string toConvert) {
		LPWSTR converted = NULL;
		const char* toConvertBuff = toConvert.c_str();
		size_t converted_chars = 0;
		TCHAR resultBuff[1000];
		mbstowcs_s(&converted_chars, resultBuff, strlen(toConvertBuff) + 1, toConvertBuff, _TRUNCATE);

		converted = resultBuff;

		return converted;
	}
}