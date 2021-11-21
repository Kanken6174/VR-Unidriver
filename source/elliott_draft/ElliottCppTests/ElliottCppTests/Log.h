#pragma once
#include <iostream>

class Log
{
public:
	/// <summary>
	/// Enum defines different log levels
	/// A log can correspond to one of three levels : Info, Level, Warning
	/// NoDisplay is only to be assigned to m_displaylevel and not to a message. No messages will show if that display level is selected.
	/// </summary>
	enum Level : char
	{
		NoDisplay,
		LevelError,
		LevelWarning,
		LevelInfo
	};

	/// <summary>
	/// Defines the current display level of our log class. User can modify it anytime.
	/// Will always show messages of a lower level, but not higher level
	/// Example : if this variable is set to Warning, Errors and Warnings will show on the console, but not Info messages
	/// </summary>
	Level m_displayLevel;

	/// <summary>Constructor for the class</summary>
	/// <param name="displayLevel">
	/// The display level you want for the class. 
	/// Set by default to warning.
	/// </param>
	Log(Level displayLevel = LevelWarning) : m_displayLevel(displayLevel) {}

	/// <summary>
	/// Abstract display method that calls upon one of the private methods according to logLevel
	/// </summary>
	/// <param name="msg">The message to display</param>
	/// <param name="logLevel">The logLevel corresponding to this message</param>
	void Disp(std::string msg, Level logLevel);
private:
	void Error(std::string msg);
	void Warning(std::string msg);
	void Info(std::string msg);
};

