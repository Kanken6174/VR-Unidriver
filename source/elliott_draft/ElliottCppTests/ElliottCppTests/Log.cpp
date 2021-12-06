#include "Log.h"


void Log::Disp(std::string msg, Level logLevel)
{
	switch (logLevel)
	{
	case Log::LevelError:
		Error(msg);
		break;
	case Log::LevelWarning:
		Warning(msg);
		break;
	case Log::LevelInfo:
		Info(msg);
		break;
	default:
		break;
	}
}

void Log::Error(std::string msg)
{
	if (m_displayLevel >= LevelError)
		std::cout << "[ERROR] " << msg << std::endl;
}

void Log::Warning(std::string msg)
{
	if (m_displayLevel >= LevelWarning)
		std::cout << "[WARNING] " << msg << std::endl;
}

void Log::Info(std::string msg)
{
	if (m_displayLevel >= LevelInfo)
		std::cout << "[INFO] " << msg << std::endl;
}
