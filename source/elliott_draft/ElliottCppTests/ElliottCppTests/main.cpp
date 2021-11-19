#include "Log.h"

int main() {
	Log log; //default constructor is called; to give display level write log(Log::LevelInfo) (for example with info)
	log.Disp("Hello world! I am a log class.", Log::LevelInfo); //should not disp with default constructor
	log.Disp("This program is quite empty!", Log::LevelWarning); //should disp with default constructor
	return 0;
}